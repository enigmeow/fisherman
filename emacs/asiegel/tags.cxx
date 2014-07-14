#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <utime.h>
#include <stdlib.h>
#include <errno.h>
#endif
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "jhash.hxx"
#include "jfile.hxx"
#include "jstring.hxx"
#include "jlist.hxx"
#include "jpad.hxx"
#include "jexception.hxx"

using namespace jbus;

#ifdef _WIN32
// cygwin style paths in output
static bool cygwin = J_FALSE;
#endif
// low-priority mode switch
static bool lowprior = J_FALSE;

class PathSet : public jManageableList<j_string> {
public:
  bool lowprior_;
  PathSet() {
    lowprior_ = lowprior;
  }
  PathSet(const PathSet& set) {
    assert(J_FALSE);
  }
  ~PathSet() { }
  void add(jCharPad& s) {
    j_string& s2 = append();
    s2.assign((char*)s, s.getsize());
  }
};


static jHash<j_string, PathSet> files_;

#define FILTER_OUT(_x)  if (memcmp(&s[(int)(l - (sizeof(_x) - 1))], _x, (sizeof(_x) - 1)) == 0) return;

void pass(jCharPad& s) {
  int l = s.getsize();

  if ((l >= 2) && (s[l-2] == '.')) {
    FILTER_OUT(".o");
    FILTER_OUT(".a");
    FILTER_OUT(".Z");
    FILTER_OUT(".z");
    FILTER_OUT(".i");
  }
  if ((l >= 3) && (s[l-3] == '.')) {
    FILTER_OUT(".so");
    FILTER_OUT(".gz");
    FILTER_OUT(".fm");
  }

  if ((l >= 4) && (s[l-4] == '.')) {
    FILTER_OUT(".DES");
    FILTER_OUT(".GIF");
    FILTER_OUT(".JPG");
    FILTER_OUT(".KEY");
    FILTER_OUT(".PDF");
    FILTER_OUT(".ZIP");
    FILTER_OUT(".au");
    FILTER_OUT(".bin");
    FILTER_OUT(".bmp");
    FILTER_OUT(".cab");
    FILTER_OUT(".cdr");
    FILTER_OUT(".cmx");
    FILTER_OUT(".dat");
    FILTER_OUT(".dep");
    FILTER_OUT(".dll");
    FILTER_OUT(".doc");
    FILTER_OUT(".dsp");
    FILTER_OUT(".dsw");
    FILTER_OUT(".elc");
    FILTER_OUT(".eps");
    FILTER_OUT(".ex_");
    FILTER_OUT(".exe");
    FILTER_OUT(".frx");
    FILTER_OUT(".ftp");
    FILTER_OUT(".gif");
    FILTER_OUT(".hdr");
    FILTER_OUT(".hhc");
    FILTER_OUT(".hhk");
    FILTER_OUT(".hhs");
    FILTER_OUT(".hlp");
    FILTER_OUT(".htm");
    FILTER_OUT(".ico");
    FILTER_OUT(".ins");
    FILTER_OUT(".jar");
    FILTER_OUT(".jpg");
    FILTER_OUT(".lib");
    FILTER_OUT(".mpp");
    FILTER_OUT(".ncb");
    FILTER_OUT(".opt");
    FILTER_OUT(".obj");
    FILTER_OUT(".OBJ");
    FILTER_OUT(".DLL");
    FILTER_OUT(".EXE");
    FILTER_OUT(".pdb");
    FILTER_OUT(".pdf");
    FILTER_OUT(".ppt");
    FILTER_OUT(".psp");
    FILTER_OUT(".qry");
    FILTER_OUT(".res");
    FILTER_OUT(".tar");
    FILTER_OUT(".xls");
    FILTER_OUT(".zip");
  }

  if ((l >= 5) && (s[l-5] == '.')) {
    FILTER_OUT(".book");
  }

  if ((l >= 6) && (s[l-6] == '.')) {
    FILTER_OUT(".class");
  }

  if ((l >= 8) && (s[l-8] == '.')) {
    FILTER_OUT(".gif_vuu");
    FILTER_OUT(".comment");
  }

  int i;
  for (i = l - 1; i >= 0; --i) 
    if (s[i] == '/' || s[i] == '\\')
      break;
  j_string key(&s[i+1], l - (i+1));
  PathSet* ps = files_.lookupValue(key);
  if (ps == NULL)
    ps = files_.add(key);
  else if (lowprior && !(ps->lowprior_))
    // The key is already in use
    return;
#ifdef _WIN32
  for (int i = 0; i < l; ++i)
    if (s[i] == '\\')
      s[i] = '/';
#endif
  ps->add(s);
}

void search(jCharPad& curdir, bool normal, unsigned int prevdirlen) {
  unsigned int curdirlen = curdir.getsize();
  if (curdirlen == 0)
    // Ignore empty strings
    return;

  if (curdir[(int)0] == '"' && curdir[(int)(curdirlen-1)] == '"') {
    // Strip enclosing quotes
    jCharPad pad(curdirlen - 2);
    memcpy((char*)pad, &curdir[1], curdirlen - 2);
    search(pad, normal, prevdirlen);
    return;
  }

  for (unsigned int i = 0; i < curdirlen; ++i)
    if (curdir[i] == ';'
#if !defined(_WIN32)
        || curdir[i] == ':'
#endif
      ) {
      // Break up combined paths
      jCharPad pad(i);
      memcpy((char*)pad, (char*)curdir, i);
      search(pad, normal, prevdirlen);

      pad.setsize(curdirlen - (i+1));
      memcpy((char*)pad, &curdir[i+1], curdirlen - (i+1));
      search(pad, normal, prevdirlen);
      return;
    }

  curdir.append('\0');
  jDirectory dir((char*)curdir);
  curdir.setsize(curdirlen);

  if (!normal) {
    try {
      dir.normalize();
    } catch (jException& ex) {
      ex.print(stderr);
      return;
    }
    normal = J_TRUE;
    curdir.setsize(0);
    curdir.append(dir.name());
    curdirlen = curdir.getsize();
  }
  if (curdirlen <= prevdirlen)
    // Prevent infinite recursion due to soft links
    return;

  fprintf(stderr, "%s ...\n", dir.name());

  class MyHandler : public jDirectory::ListHandler {
  public:
    jCharPad& curdir_;
    bool normal_;
    MyHandler(jCharPad& curdir, bool normal)
      : curdir_(curdir), normal_(normal_)
      { }
    virtual ~MyHandler() { }
    virtual void entry(const char* name, bool isdir) {
      if (strcmp(name, "CVS") == 0 || strcmp(name, ".svn") == 0)
        return;
      unsigned int curdirlen = curdir_.getsize();
#if defined(_WIN32)
      curdir_.append('\\');
#else
      curdir_.append('/');
#endif
      curdir_.append(name);
      if (isdir) {
        try {
          search(curdir_, normal_, curdirlen);
        } catch (jException& ex) {
          ex.print(stderr);
        }
      } else
        pass(curdir_);
      curdir_.setsize(curdirlen);
    }
  };
  MyHandler hand(curdir, normal);
  dir.list(hand);
}

static void usage(const char* prog) {
  fprintf(stderr, "usage: %s "
#ifdef _WIN32
    "[-c]"
#endif
    " <directory> ... [-l] <directory> ...\n", prog);
  exit(1);
}

int main(int argc, char** argv) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (int j = 1; argv[i][j] != '\0'; ++j) {
        switch(argv[i][j]) {
#ifdef _WIN32
        case 'c':
          cygwin = J_TRUE;
          break;
#endif
        case 'l':
          lowprior = J_TRUE;
          fprintf(stderr, "Switching to low priority...\n");
          break;
        default:
          usage(argv[0]);
        }
      }
      continue;
    }
    jCharPad curdir;
    curdir.append(argv[i]);
    search(curdir, J_FALSE, 0);
  }

  printf("(setq completion-ignore-case 't)\n");
#ifdef USER_jsiegel
  printf("(defun vtfile (file)\n");
#else
  printf("(defun goto-file (file)\n");
#endif
  printf("  (interactive (list (completing-read \"File: \" goto-files nil t)))\n");
  printf("  (let (newlist)\n");
  printf("    (setq newlist (car (cdr (assoc file goto-files))))\n");
  printf("    (if (> (length newlist) 1)\n");
  printf("        (find-file-other-window (completing-read \"Which one? \" (mapcar 'list newlist)))\n");
  printf("      (find-file-other-window (car newlist))\n");
  printf("      )\n");
  printf("    )\n");
  printf(")\n");
  printf("(setq goto-files (list\n");

  jHashEntry<j_string, PathSet>* ent;
  unsigned int pos = files_.firstPos();
  while ((ent = files_.nextKeyValue(pos)) != NULL) {
    printf( "(list \"%s\" (list", (const char*)(ent->key_));
    PathSet* ps = &(ent->value_);
    for (unsigned int j = 0; j < ps->length(); j++) {
      const char* path = (*ps)[j];
      fputs(" \"", stdout);
#ifdef _WIN32
      if (cygwin) {
	if (path[1] == ':') {
	  fputs("/cygdrive/", stdout);
	  fputc(path[0], stdout);
	  path += 2;
	}
      }
#endif      
      while (*path != '\0') {
	char c = *(path++);
#ifdef _WIN32
        if (c == '\\')
	  fputc('/', stdout);
	else
	  fputc(c, stdout);
#else
	fputc(c, stdout);
#endif
      }
      fputs("\"", stdout);
    }
    printf("))\n");
  }
  printf("))\n");
  return 0;
}
