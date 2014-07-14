#include "stdafx.h"
#include "Form1.h"
#include <psapi.h>


/**
 * Welcome to Billy the fisherman
 *  Written by Josh Siegel (jsiegel@stormbirds.org) so that Enigmeow
 *    and Ebb Oh Knee can get that last fish.  
 *
 * Thanks go out to Boop and Freeloader for acting as sounding boards
 * during the creation of this.
 *
 * This is NOT open source.. and not public yet.  You do not have
 * permission to redistribute this.  If you wish to help me make it
 * better, I am very much open for assistance
 *
 * Notes on toontown
 *  it takes 4500ms to rotate 360
 *   movement is .016 units per ms
 *
 * Below is my notes on the mathmatics required to cast a fishing line
 * to a destination.  Problem is, it only seems to work on a 1000x1000
 * screen dispite the fact we tried to make it scale properly.  I will
 * have to revisit this as soon as the rest of the functionality is
 * working correctly
 *
 * ***ORIGINAL***															***REVISED***
 *  deltax_ = window-offset-to-client-x + window_x_pos						deltax_ = window-offset-to-client-x + window_x_pos
 *  deltay_ = window-offset-to-client-y + window_y_pos						deltay_ = window-offset-to-client-y + window_y_pos
 *  wx_ = client-width														wx_ = client-width
 *  wy_ = client-height														wy_ = client-height
 *  scalex_ = wx_ / 1000.0													scalex_ = wx / 1000.0
 *  scaley_ = wy_ / 1000.0													scaley_ = wy / 1000.0
 *  cast_spot_x_ = 500     *  on a 1000x1000 screen							cast_spot_x_ = wx_ * 0.5
 *  cast_spot_y_ = 735     *  on a 1000x1000 screen							cast_spot_y_ = wy_ * 0.73542
 *  scaled_cast_spot_x_ = cast_spot_x_ * scalex_							scaled_cast_spot_x_ = wx_ * 0.5	(not needed-see cast_spot_x_ above, keep if easier for re-write)
 *  scaled_cast_spot_y_ = cast_spot_y_ * scaley_							scaled_cast_spot_y_ = wy_ * 0.73542	(not needed-see cast_spot_y_ above, keep if easier for re-write)	
 *  cx_ = scaled_cast_spot_x_ + deltax_										cx_ = cast_spot_x_ + deltax_
 *  cy_ = scaled_cast_spot_y_ + deltay_										cy_ = cast_spot_y_ + deltay_
 * 
 *  dx = target x pixel on screen											dx = target x pixel on screen
 *  dy = target y pixel on screen											dy = target y pixel on screen
 * 
 *  dx = (scaled_cast_spot_x_ - ((5 - (casty/100.0))*castx))				dx = (cast_spot_x - ((5 - (casty/100.0))*castx))
 *  dy = (scaled_cast_spot_y_ - (casty*2.75)) * scalex_						dy = (cast_spot_y_ - (casty*2.75)) * scalex_
 * 
 *  casty = (scaled_cast_spot_y_ - (dy_ * (1000.0 / wy_))) / 2.75			casty = (cast_spot_y_ - (dy_ * (1000.0 / wy_))) / 2.75
 *  castx = (100.0 * (dx_ - scaled_cast_spot_x_)) / (casty_ - 500.0)		castx = (100.0 * (dx_ - cast_spot_x_)) / (casty_ - 500.0)
 * 
 * Color samples and locations
 * 
 *  ready to fish - 500 735 (253 0 2)
 *  got fish      - 500 735 (205 127 127)
 *  full bucket   - 509 641 (205 63 61)
 *  sell fish     - 724 780 (139 158 224)
 *
 * To be done before first public release:
 *
 *  3) Fix the scaling issues so that we can deal with different sized
 *     windows
 *  6) Make all the delays/factors configurable and persistant
 *  7) change getPosition() to use fstat()
 *  8) See if this will correctly find the log files for people using
 *     the Spoofer to run multiple toons instead of just doing what I
 *     do which is make copies of the Toontown installation directory
 *  9) Accuracy of fishing sucks on fast moving fish
 * 11) Sometimes on reshaping windows (reshapeButton), it leaves
 *     toontown in a messed up state where it does not recognize the
 *     mouse is over the various buttons.  I would like to either 
 *      a) Fix this
 *      b) make reshaping the windows not required
 *     The reason I want to fix it is that I want to make a convenient
 *     button to lay out all my toons in the pattern I like.  So,
 *     while it is not directly related to fishing, I want to figure
 *     it out
 * 13) Is there any way to send mouseEvents without using
 *     SetCursorPos()?    It would be nice to be able to send
 *     mouseEvents to windows without focus
 * 14) switch startCast() over to not use SCALEX and SCALEY and use
 *     the precomputed values... part of moving all the math into one
 *     part of the code to improvement maintainability. Same with
 *     doCast()
 * 17) centerFish() reuses the same code multiple times and still
 *     results in a crappy result.  Once the math is fixed for
 *     scaling the windows,  we need to improve how well this POS
 *     works and make the code something I am willing to be proud of
 * 19) Why, when I have a full bucket, do I need to try to click the
 *     left mouse button multiple times while wigging the mouse.  This
 *     is not correct which means there must be something other
 *     mitigating issue
 * 21) Make the constants (4500 and 0.016) user configurable so that
 *     everything can work on "speed".  Maybe I should just make
 *     things work on speed by me tuning it myself.  A lot of the
 *      timing expectations are going to be mangled by speed.
 * 23) Make the UI not suck - where is my warm/fuzzy?
 * 25) Support estate fishing
 * 26) give me a way of enabling and disabling toons from the fishing
 *     system.
 *
 **/

#define SCALEX(_x) ((int) (((float) (_x)) * pi_->scalex_ + pi_->deltax_))
#define SCALEY(_y) ((int) (((float) (_y)) * pi_->scaley_ + pi_->deltay_))

using namespace fisherman;
using namespace System;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Runtime::Serialization;
using namespace System::Runtime::Serialization::Formatters::Binary;

#include "golf.hxx"

extern "C" {
  BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
};

#define NT_SUCCESS(x) ((x) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

typedef NTSTATUS (NTAPI *_NtQuerySystemInformation)(ULONG SystemInformationClass,
  PVOID SystemInformation,
  ULONG SystemInformationLength,
  PULONG ReturnLength);

typedef NTSTATUS (NTAPI *_NtDuplicateObject)(HANDLE SourceProcessHandle,
  HANDLE SourceHandle,
  HANDLE TargetProcessHandle,
  PHANDLE TargetHandle,
  ACCESS_MASK DesiredAccess,
  ULONG Attributes,
  ULONG Options);
typedef NTSTATUS (NTAPI *_NtQueryObject)(HANDLE ObjectHandle,
  ULONG ObjectInformationClass,
  PVOID ObjectInformation,
  ULONG ObjectInformationLength,
  PULONG ReturnLength);

typedef struct _UNICODE_STRING {
  USHORT Length;
  USHORT MaximumLength;
  PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _SYSTEM_HANDLE {
  ULONG ProcessId;
  BYTE ObjectTypeNumber;
  BYTE Flags;
  USHORT Handle;
  PVOID Object;
  ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION {
  ULONG HandleCount;
  SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef enum _POOL_TYPE {
  NonPagedPool,
  PagedPool,
  NonPagedPoolMustSucceed,
  DontUseThisType,
  NonPagedPoolCacheAligned,
  PagedPoolCacheAligned,
  NonPagedPoolCacheAlignedMustS
} POOL_TYPE, *PPOOL_TYPE;

typedef struct _OBJECT_TYPE_INFORMATION {
  UNICODE_STRING Name;
  ULONG TotalNumberOfObjects;
  ULONG TotalNumberOfHandles;
  ULONG TotalPagedPoolUsage;
  ULONG TotalNonPagedPoolUsage;
  ULONG TotalNamePoolUsage;
  ULONG TotalHandleTableUsage;
  ULONG HighWaterNumberOfObjects;
  ULONG HighWaterNumberOfHandles;
  ULONG HighWaterPagedPoolUsage;
  ULONG HighWaterNonPagedPoolUsage;
  ULONG HighWaterNamePoolUsage;
  ULONG HighWaterHandleTableUsage;
  ULONG InvalidAttributes;
  GENERIC_MAPPING GenericMapping;
  ULONG ValidAccess;
  BOOLEAN SecurityRequired;
  BOOLEAN MaintainHandleCount;
  USHORT MaintainTypeList;
  POOL_TYPE PoolType;
  ULONG PagedPoolUsage;
  ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;


char* UnicodeToUtf8( const WCHAR* wstr )
{
  const WCHAR* w;

  int len = 0;
  for ( w = wstr; *w; w++ ) {
    if ( *w < 0x0080 ) len++;
    else if ( *w < 0x0800 ) len += 2;
    else len += 3;
  }
       
  unsigned char* szOut = ( unsigned char* )malloc( len+1 );
  if ( szOut == NULL )
    return NULL;
       
  int i = 0;
  for ( w = wstr; *w; w++ ) {
    if ( *w < 0x0080 )
      szOut[i++] = ( unsigned char ) *w;
    else if ( *w < 0x0800 ) {
      szOut[i++] = 0xc0 | (( *w ) >> 6 );
      szOut[i++] = 0x80 | (( *w ) & 0x3f );
    } else {
      szOut[i++] = 0xe0 | (( *w ) >> 12 );
      szOut[i++] = 0x80 | (( ( *w ) >> 6 ) & 0x3f );
      szOut[i++] = 0x80 | (( *w ) & 0x3f );
    } 
  }
       
  szOut[ i ] = '\0';
  return ( char* )szOut;
}

PVOID GetLibraryProcAddress(PSTR LibraryName, PSTR ProcName) {
  return GetProcAddress(GetModuleHandleA(LibraryName), ProcName);
}
#define BUFSIZE 512

void NormalizeFileName(const char *src, char *dst) 
{
  char szDrive[3] = TEXT("c:");
  char drives[BUFSIZE];
  drives[0] = '\0';

  GetLogicalDriveStrings(BUFSIZE-1, drives);

  const char *p = drives;
  while (*p && p < &drives[BUFSIZE]) {
    TCHAR szName[MAX_PATH];

    szDrive[0] = *p;
    QueryDosDevice(szDrive, szName, MAX_PATH);
    int slen = strlen(szName);
    if (strncmp(src, szName, slen) == 0) {
      sprintf(dst,"%s%s", p, &src[slen + 1]);
      return;
    }
    p += 4;
  }
}

_NtQuerySystemInformation NtQuerySystemInformation = 0;
_NtDuplicateObject NtDuplicateObject = 0;
_NtQueryObject NtQueryObject = 0;

HKL keyBHandle = NULL;

class fishVector {
public:
  int valcnt_;
  double *vals_;

  fishVector() : valcnt_(0), vals_(0) {}
  ~fishVector() {if (vals_ != 0) free(vals_);  }

  void set(int cnt, ...) {
    valcnt_ = cnt;
    vals_ = (double *) malloc(sizeof(double) * cnt);
    va_list ap;
    va_start(ap, cnt);
    for (int i = 0; i < cnt; i++) {
      double v = va_arg(ap, double);
      vals_[i] = v;
    }
    va_end(ap);
  }

  void setV(int cnt, double *vals) {
    vals_ = (double *) malloc(sizeof(double) * cnt);
    for (int i = 0; i < cnt; i++) 
      vals_[i] = vals[i];
    valcnt_ = cnt;
  }
  double distance(const fishVector &ov) {
    double ret = 0;

    if (ov.valcnt_ == this->valcnt_) {
      for (int i = 0; i < this->valcnt_; i++)  
        ret += fabs(ov.vals_[i] - this->vals_[i]);
      return ret;
    }

    for (int i = 0; i < valcnt_; i++)  {
      int best = -1;
      double dist = -1;
      for (int y = 0; y < ov.valcnt_; y++)  {
        double d = fabs(ov.vals_[y] - this->vals_[i]);
        if ((best == -1) || (d < dist)) {
          dist = d;
          best = y;
        }
      }
      ret += dist;
    }
    return ret;
  }
};

fishVector raceVectors[8];
fishVector raceGrand[2];

void loadRaceVectors() {
  double gp1[] = {13.5416666666667, 13.9236111111111}; // 500    13.2888888888889, 13.5555555555556, 13.9111111111111
  double gp2[] = {13.3680555555556, 13.75};            // 1000   13.1111111111111, 13.3777777777778, 13.7555555555556, 13.8666666666667
  raceGrand[0].setV(sizeof(gp1) / sizeof(gp1[0]), gp1);
  raceGrand[1].setV(sizeof(gp2) / sizeof(gp2[0]), gp2);
  
  double cc1[] = {0, 13.125, 13.6458333333333};
  double cc2[] = {0, 13.0902777777778, 13.1944444444444, 13.6458333333333};
// city circuit       300  13.0902777777778, 13.6805555555556
  raceVectors[0].setV(sizeof(cc1) / sizeof(cc1[0]), cc1);
  raceVectors[7].setV(sizeof(cc2) / sizeof(cc2[0]), cc2);

  double bb[] = {0, 13.0902777777778, 13.6458333333333};
// blizzard boulevard 400 13.0902777777778, 13.2986111111111, 13.4375, 13.6805555555556
  raceVectors[1].setV(sizeof(bb) / sizeof(bb[0]), bb);

  double cs[] = {0, 13.0555555555556, 13.4027777777778, 13.6111111111111};
// corkscrew statium 50 
  raceVectors[2].setV(sizeof(cs) / sizeof(cs[0]), cs);

  double ccol[] = {0, 13.125, 13.3680555555556};
  raceVectors[3].setV(sizeof(ccol) / sizeof(ccol[0]), ccol);
// corkscrew coliseum 75

  double rr[] = {0, 13.0902777777778, 13.4722222222222, 13.8194444444444};
  raceVectors[4].setV(sizeof(rr) / sizeof(rr[0]), rr);
// rustic raceway 100
//
  double aa1[] = {0, 13.0902777777778, 13.8194444444444};
  raceVectors[5].setV(sizeof(aa1) / sizeof(aa1[0]), aa1);

  double aa2[] = {0, 13.0902777777778, 13.2638888888889, 13.5763888888889, 13.8194444444444};
  raceVectors[6].setV(sizeof(aa2) / sizeof(aa2[0]), aa2);
// airborne acres 150
//
}

fishVector vectors[11];

void loadFishVectors() {
  // afternoon tea 0.336, 0.35, 0.365, 0.395, 0.415, 0.44, 0.451, 0.47, 0.484, 0.503, 0.52, 0.539, 0.556, 0.573, 0.587, 0.624, 0.645, 0.669
  double at[] = {0.336, 0.35, 0.365, 0.395, 0.415, 0.44, 0.451, 0.47, 0.484, 0.503, 0.52, 0.539, 0.556, 0.573, 0.587, 0.624, 0.645, 0.669};
  vectors[0].setV(sizeof(at) / sizeof(at[0]), at);

  // down the hatch 0.304, 0.318, 0.338, 0.354, 0.384, 0.414, 0.428, 0.465, 0.486, 0.503, 0.52, 0.556, 0.573, 0.594, 0.608, 0.631, 0.653, 0.669, 0.687, 0.704
  double dth[] = {0.304, 0.318, 0.338, 0.354, 0.384, 0.414, 0.428, 0.465, 0.486, 0.503, 0.52, 0.556, 0.573, 0.594, 0.608, 0.631, 0.653, 0.669, 0.687, 0.704};
  vectors[1].setV(sizeof(dth) / sizeof(dth[0]), dth);

  // hole in fun  0, 0.372, 0.388, 0.406, 0.423, 0.441, 0.467, 0.504, 0.523, 0.537, 0.567, 0.591, 0.603, 0.621, 0.635
  double hif[] = {0.372, 0.388, 0.406, 0.423, 0.441, 0.467, 0.504, 0.523, 0.537, 0.567, 0.591, 0.603, 0.621, 0.635};
  vectors[2].setV(sizeof(hif) / sizeof(hif[0]), hif);

  // hole on the range , 0.283, 0.3, 0.317, 0.334, 0.353, 0.378, 0.414, 0.431, 0.448, 0.462, 0.5, 0.52, 0.537, 0.554, 0.59, 0.601, 0.625, 0.639, 0.654, 0.668, 0.686, 0.704, 0.718
  double hotf[] = {0.283, 0.3, 0.317, 0.334, 0.353, 0.378, 0.414, 0.431, 0.448, 0.462, 0.5, 0.52, 0.537, 0.554, 0.59, 0.601, 0.625, 0.639, 0.654, 0.668, 0.686, 0.704, 0.718};
  vectors[3].setV(sizeof(hotf) / sizeof(hotf[0]), hotf);

  // holy mackerel 0.298, 0.315, 0.332, 0.349, 0.368, 0.393, 0.424, 0.465, 0.477, 0.488, 0.513, 0.527, 0.544, 0.56, 0.579, 0.59, 0.61, 0.634, 0.645, 0.665, 0.689
  double hm[] = {0.298, 0.315, 0.332, 0.349, 0.368, 0.393, 0.424, 0.465, 0.477, 0.488, 0.513, 0.527, 0.544, 0.56, 0.579, 0.59, 0.61, 0.634, 0.645, 0.665, 0.689};
  vectors[4].setV(sizeof(hm) / sizeof(hm[0]), hm);

  // hot links 0.387, 0.404, 0.422, 0.439, 0.464, 0.496, 0.523, 0.542, 0.556, 0.577, 0.588, 0.617
  double hl[] = {0.387, 0.404, 0.422, 0.439, 0.464, 0.496, 0.523, 0.542, 0.556, 0.577, 0.588, 0.617};
  vectors[5].setV(sizeof(hl) / sizeof(hl[0]), hl);

  // one little birdie  0, 0.299, 0.316, 0.334, 0.348, 0.367, 0.402, 0.429, 0.457, 0.484, 0.504, 0.53, 0.565, 0.578, 0.595, 0.615, 0.626, 0.647, 0.661, 0.681, 0.702
  double olb[] = {0.299, 0.316, 0.334, 0.348, 0.367, 0.402, 0.429, 0.457, 0.484, 0.504, 0.53, 0.565, 0.578, 0.595, 0.615, 0.626, 0.647, 0.661, 0.681, 0.702};
  vectors[6].setV(sizeof(olb) / sizeof(olb[0]), olb);

  // peanut butter0, 0.335, 0.361, 0.39, 0.404, 0.419, 0.433, 0.453, 0.465, 0.49, 0.523, 0.551, 0.563, 0.588, 0.615, 0.636, 0.66, 0.671
  double pb[] = {0.335, 0.361, 0.39, 0.404, 0.419, 0.433, 0.453, 0.465, 0.49, 0.523, 0.551, 0.563, 0.588, 0.615, 0.636, 0.66, 0.671};
  vectors[7].setV(sizeof(pb) / sizeof(pb[0]), pb);

  // seeing green 0.362, 0.383, 0.407, 0.433, 0.453, 0.467, 0.485, 0.503, 0.528, 0.545, 0.56, 0.571, 0.591, 0.615, 0.639, 0.653
  double sg[] = {0.362, 0.383, 0.407, 0.433, 0.453, 0.467, 0.485, 0.503, 0.528, 0.545, 0.56, 0.571, 0.591, 0.615, 0.639, 0.653};
  vectors[8].setV(sizeof(sg) / sizeof(sg[0]), sg);

  // swing a long  0.338, 0.371, 0.404, 0.423, 0.437, 0.455, 0.473, 0.491, 0.516, 0.53, 0.549, 0.57, 0.597, 0.613, 0.631, 0.645, 0.663, 0.681
  double sal[] = {0.338, 0.371, 0.404, 0.423, 0.437, 0.455, 0.473, 0.491, 0.516, 0.53, 0.549, 0.57, 0.597, 0.613, 0.631, 0.645, 0.663, 0.681};
  vectors[9].setV(sizeof(sal) / sizeof(sal[0]), sal);

  // swing time  0.377, 0.41, 0.442, 0.462, 0.476, 0.494, 0.511, 0.544, 0.566, 0.59, 0.601, 0.613, 0.633
  double st[] = {0.377, 0.41, 0.442, 0.462, 0.476, 0.494, 0.511, 0.544, 0.566, 0.59, 0.601, 0.613, 0.633};
  vectors[10].setV(sizeof(st) / sizeof(st[0]), st);
}

// Converting keycodes into keyboard scan codes
unsigned char getScanCode(unsigned int keycode) {
  if (keyBHandle == NULL) 
    keyBHandle = LoadKeyboardLayout("00000409",0);
  unsigned int ret = MapVirtualKeyEx(keycode,MAPVK_VK_TO_VSC,keyBHandle);
  return ret;
}

//Making a set of keydata
unsigned int mkKeyData(
  short repCnt,/*How many times the key have been repeated so far*/
    unsigned char ScanCode,/*The scancode of the keyboard*/
    bool hAlt,/*Is the key pressed with ALT?*/
    bool inRep,/*Is the key part of a repetive sequence?*/
    bool isRel/*Is the key beeing released?*/ ) {
  int ret = 0;
  int irepCnt = repCnt;
  int iScanCode = ScanCode;
  int ihAlt = hAlt ? 1 : 0;
  int iinRep = inRep ? 1 : 0;
  int iisRel = isRel ? 1 : 0;
  //Rotate the data to their bitwise positions
  irepCnt <<= 0;
  iScanCode <<= 16;
  ihAlt <<= 29;
  iinRep <<= 30;
  iisRel <<= 31;
  //OR them all together
  ret = irepCnt | iScanCode | ihAlt | iinRep | iisRel;
  //Return it, packed and ready
  return ret;
}

/**
 * A pond right now is configured only by setting the size of the
 * pond, color tolerances of the fish, and where the docks and
 * fisherman are.  
 */
[Serializable]
public ref class pondConfig {
public:
  String ^description_;
  int pondx_;
  int pondy_;
  int pondw_;
  int pondh_;
  int fishr_;
  int fishg_;
  int fishb_;
  int fisht_;
  float dockx_;
  float docky_;
  float fisherx_;
  float fishery_;
  bool estate_;
};

enum ToonStateEnums {
  STATE_NULL,
  STATE_SELL_FISH,
  STATE_RUNNING,
  STATE_ON_DOCK,
  STATE_GOT_FISH,
  STATE_GOING_TO_SELL_FISH,
  STATE_GOING_TO_DOCK,
  STATE_GOING_TO_CART,
  STATE_AT_GOLF_MIDPOINT,
  STATE_READY_TO_JUMP_ON,
  STATE_ON_CART,
  STATE_GOLFING,
  STATE_RACE_PAUSE,
  STATE_RACE_PLAYGROUND,     // random location in playground
  STATE_RACE_PRELAUNCH,      // near correct track
  STATE_RACE_LAUNCH,         // near lauch pad
  STATE_RACE_ONCART,         // On cart but everything not verified yet
  STATE_RACE_READY_TO_RACE,  // all checks have passed.. waiting to hit 'play'
  STATE_RACE_RACING,         // actually racing
};

struct ToonPos {
  float _x;
  float _y;
  float _z;
  float _h;
};

class MemBuffer {
public:
  MemBuffer() {
    ptr_ = 0;
    next_ = 0;
    addr_ = 0;
    size_ = 0;
  }
  ~MemBuffer() {
    if (ptr_ != 0)
      free(ptr_);
  }
  void * addr_;
  int size_;
  char *ptr_;
  MemBuffer *next_;
};


ref class FloatSetObj {
public:
  int xi_;
  int yi_;
  int zi_;
  int hi_;

  FloatSetObj(double x, double y, double z, double h)  {
    xi_ = (int) (x * 100.0);
    yi_ = (int) (y * 100.0);
    zi_ = (int) (z * 100.0);
    hi_ = (int) (h * 100.0);
  }

  int size() {  
    return sizeof(float) * 4; 
  }

  int cmp(const char *val) { 
    struct ToonPos *tp = (struct ToonPos *) val;
    return ((int) (100.0 * tp->_x) == xi_) && 
      (((int) (100.0 * tp->_y)) == yi_) && 
      (((int) (100.0 * tp->_z))== zi_) && 
      (((int) (100.0 * tp->_h)) == hi_);
  }
};

class SnapShot {
public:
  MemBuffer *data_;
  DWORD hProcess_;
  int elements_;

  SnapShot(DWORD hProcess) :  hProcess_(hProcess) { 
    data_ = NULL;
    elements_ = 0;
  }

  ~SnapShot() { 
    clear();
  }

  void clear() { 
    while (data_ != NULL) {
      MemBuffer *n = data_;
      data_ = data_->next_;
      delete n;
    }
  }

  static BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege) {
    TOKEN_PRIVILEGES tp;
    LUID luid;

    HANDLE hToken;

    if (!OpenProcessToken (GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return FALSE;

    if ( !LookupPrivilegeValue(NULL, lpszPrivilege, &luid ) )
      return FALSE; 

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    if (bEnablePrivilege)
      tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    else
      tp.Privileges[0].Attributes = 0;

    if ( !AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES) NULL, (PDWORD) NULL) ) 
      return FALSE; 

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
      return FALSE;

    CloseHandle(hToken);

    return TRUE;
  }

  static void reportError() {
    int err = WSAGetLastError();

    char message[256];
    sprintf(&message[0], "Windows error %d", err);
    ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
      NULL, err, 0, (LPTSTR)&message[0], sizeof(message), NULL);
  }

  int trim(BOOL changed) {
    MemBuffer **prev = &data_;
    MemBuffer *cur = data_;
    int elements = 0;

    HANDLE process=OpenProcess(PROCESS_ALL_ACCESS, FALSE, hProcess_);

    while (cur != NULL) {
      char buf[255];
      SIZE_T lpRead;
      ReadProcessMemory( process, cur->addr_, buf, cur->size_, &lpRead);
      if (changed ? (memcmp(buf, cur->ptr_, cur->size_) != 0) : (memcmp(buf, cur->ptr_, cur->size_) == 0)) {
        MemBuffer *t = cur;
        *prev = t->next_;
        cur = t->next_;
        delete t;
      } else {
        memcpy(cur->ptr_, buf, cur->size_);
        prev = &cur->next_;
        cur = cur->next_;
        elements++;
      }
    }
    CloseHandle(process);

    elements_ = elements;
    return elements;
  }

  int trim(FloatSetObj ^cobj) {
    MemBuffer **prev = &data_;
    MemBuffer *cur = data_;
    char buf[255];
    int elements = 0;
    SIZE_T lpRead;

    HANDLE process=OpenProcess(PROCESS_ALL_ACCESS, FALSE, hProcess_);

    while (cur != NULL) {
      ReadProcessMemory( process, cur->addr_, buf, cur->size_, &lpRead);
      if (!cobj->cmp(buf)) {
        MemBuffer *t = cur;
        *prev = t->next_;
        cur = t->next_;
        delete t;
      } else {
        memcpy(cur->ptr_, buf, cur->size_);
        prev = &cur->next_;
        cur = cur->next_;
        elements++;
      }
    }
    CloseHandle(process);

    elements_ = elements;
    return elements;
  }

  int searchAndSnap(FloatSetObj ^cobj, BOOL quick, HANDLE proc, char * skip) {
    clear();

    SIZE_T lpRead;
    int elements = 0;

    MemBuffer *n;

    SYSTEM_INFO lpSysInfo;
    GetSystemInfo(&lpSysInfo);
    HANDLE process;
    if (proc != NULL)
      process = proc;
    else
      process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, hProcess_);
    char * start = (skip == 0) ? (char *) lpSysInfo.lpMinimumApplicationAddress : (skip + 4);

    while(start < lpSysInfo.lpMaximumApplicationAddress) {
      MEMORY_BASIC_INFORMATION mbi;

      int sz = VirtualQueryEx( process, (void *)start, &mbi, sizeof(MEMORY_BASIC_INFORMATION));

      if((mbi.State == MEM_COMMIT) && (mbi.Protect != PAGE_READONLY) && (mbi.Protect != PAGE_EXECUTE_READ)
        && (mbi.Protect != PAGE_GUARD) && (mbi.Protect != PAGE_NOACCESS)) {
        char *p = (char *)malloc(mbi.RegionSize);
        do {
          if(!ReadProcessMemory( process, (void *)start, p, mbi.RegionSize, &lpRead)) 
            break;

          if(mbi.RegionSize != lpRead) 
            break;

          const char *ptr = p;
          const char *eptr = p + mbi.RegionSize;

          while (ptr < eptr) {
            if (cobj->cmp(ptr)) {
              MemBuffer *b = new MemBuffer();

              b->size_ = cobj->size();
              b->ptr_ = (char *)malloc(b->size_);
              b->addr_ = (char *) start + (ptr - p);
              memcpy(b->ptr_, ptr, b->size_);

              if (data_ == NULL)
                data_ = b;
              else 
                n->next_  = b;
              n = b;
              elements++;
              if (quick)  {
                free(p);
                if (proc == NULL)
                  CloseHandle(process);
                elements_ = elements;
                return elements;
              }
            }
            ptr += 4; // who knows how things are aligned...
          }
        } while(0);
        free(p);
      }

      start += mbi.RegionSize;
    }

    if (proc == NULL)
      CloseHandle(process);

    elements_ = elements;
    return elements;
  }
};


 public ref class ToonState {
 public:
   int turnstate_;
   int followstate_;
   int state_;
   int rstate_;
   int rstate2_;
   double tleft_;
   double tright_;
   bool second_;
   bool selected_;
   int cycle_;
   int cycle2_;
   int cycle3_;
   String^ toonName_;
   DWORD dwProcessId_;
   DWORD windowId_;
   void* base_;
   HANDLE process_;
   HWND hWnd_;
   HBITMAP hBitmap1_;
   BITMAPINFO *bmi1_;
   void *bits1_;
   HBITMAP hBitmap2_;
   BITMAPINFO *bmi2_;
   void *bits2_;
   HBITMAP hScanmap_;
   HDC hdcDest_;
   HDC hdcSrc_;
   HDC fish1_;
   HDC fish2_;
   HDC toonView_;
   bool firstHit_;

   HANDLE flog_;
   char *logFile_;
   float x_,y_,z_,h_;
   float tx_, ty_;
   int zone_;

   int deltax_;                 // window-offset-to-client-x + window_x_pos
   int deltay_;                 // window-offset-to-client-y + window_y_pos
   double wx_;                  // client-width
   double wy_;                  // client-height
   double cast_spot_x_;         // 500  on a 1000x1000 screen
   double cast_spot_y_;         // 735  on a 1000x1000 screen
   double scaled_cast_spot_x_;  // cast_spot_x_ * scalex_
   double scaled_cast_spot_y_;  // cast_spot_y_ * scaley_
   double cx_;                  // scaled_cast_spot_x_ + deltax_
   double cy_;                  // scaled_cast_spot_y_ + deltay_
   double fullbucketx_;                  // scaled_cast_spot_x_ + deltax_
   double fullbuckety_;                  // scaled_cast_spot_x_ + deltax_
   double sellfishx_;                  // scaled_cast_spot_x_ + deltax_
   double sellfishy_;                  // scaled_cast_spot_x_ + deltax_
   double scalex_;              // wx_ / 1000.0
   double scaley_;              // wy_ / 1000.0

   pondConfig ^pc_;

 public:
   ToonState( String^ toonName,   DWORD dwProcessId, HWND hWnd,  const char *logFile, pondConfig ^pc) {
     this->turnstate_ = 0;
     this->followstate_ = 0;
     this->tleft_ = 0;
     this->tleft_ = 0;
     this->cycle_ = 0;
     this->cycle2_ = 0;
     this->cycle3_ = 0;
     this->rstate_ = 1;
     this->rstate2_ = 0;
     this->toonName_ = toonName;
     this->dwProcessId_ = dwProcessId;
     this->hWnd_ = hWnd;
     this->base_ = 0;
     this->process_ = 0;
     this->logFile_ = _strdup(logFile);
     this->flog_ =  CreateFile(logFile, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
       OPEN_EXISTING, (FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN), 0);
     DWORD ret = SetFilePointer(this->flog_, 0, 0, FILE_END);

     zone_ = 0;
     state_ = STATE_ON_DOCK;
     pc_ = pc;
   }

   property String^ ShortName {
     String^ get() {
       return toonName_;
     }
   }

   property String^ LongName {
     String^ get() {
       return toonName_;
     }
   }
   virtual String^ ToString() override {
     return String::Concat( this->toonName_, " (", this->dwProcessId_  + ")");
   }

   /**
    * This bit of black magic will read the current position of the toon
    *  out of the log file.  This works remarkably well for being
    *  stateless.  If this were a invasion monitoring application, we
    *  would keep the log open continusly
    */

   bool putPosition() {
     if (base_ != 0) {
       char buf[255];
       SIZE_T lpWrite;
       struct ToonPos *tp = (struct ToonPos *) &buf[0];
       tp->_x = this->x_;
       tp->_y = this->y_;
       tp->_z = this->z_;
       tp->_h = this->h_;
       if (WriteProcessMemory( this->process_, base_, buf, sizeof(struct ToonPos), &lpWrite))
         return true;
       else
         return false;
     }
     return false;
   }

   void getPosition() {
     if (base_ != 0) {
       SIZE_T lpRead;
       char buf[255];

       if (ReadProcessMemory( this->process_, base_, buf, sizeof(struct ToonPos), &lpRead)) {
         struct ToonPos *tp = (struct ToonPos *) &buf[0];
         this->x_ = tp->_x;
         this->y_ = tp->_y;
         this->z_ = tp->_z;
         this->h_ = tp->_h;
       }
     } else {
       // This could probably be done with a ftell or fstat call but I
       // was having some linking issues under dot net and its
       // interactions with the fstat buffer.   
       FILE *log = fopen(logFile_, "r");
       fseek (log, 0, SEEK_END);
       int pos = ftell(log);
       fclose(log);

       ::SendMessage(hWnd_, WM_KEYDOWN, VK_LSHIFT, 0);
       ::SendMessage(hWnd_, WM_KEYDOWN, VK_F1, 0);
       ::SendMessage(hWnd_, WM_KEYUP, VK_F1, 0);
       ::SendMessage(hWnd_, WM_KEYUP, VK_LSHIFT, 0);
       Sleep(100); // is this a long enough delay?

       log = fopen(logFile_, "r");
       fseek (log, pos, SEEK_SET);

       char buf[255];
       while (fgets(buf, sizeof(buf), log) != NULL) {
         if (strlen(buf) < 60)
           continue;
         if (strncmp(buf, "Current position=", 16) == 0) {
           char dist[255];
           sscanf(buf, "Current position= (%f,  %f, %f ), H: %f, Zone: %d,, Ver: %s, , District: %s",
             &x_, &y_, &z_, &h_, &zone_, dist);
           break;
         }
       }
       fclose(log);
       log = NULL;

       Sleep(300); // I wish we did not have to wait before sending a
       // . and return .. 

       ::SendMessage(hWnd_, WM_KEYDOWN, '.', 0);
       int kd = mkKeyData(1,getScanCode('.'),false,false,false);
       ::SendMessage(hWnd_, WM_CHAR, '.', kd);
       ::SendMessage(hWnd_, WM_KEYUP, '.', 0);
       ::SendMessage(hWnd_, WM_KEYDOWN, VK_RETURN, 0);
       ::SendMessage(hWnd_, WM_KEYUP, VK_RETURN, 0);
     }
   }

   System::Void findbase() {
     do {
       this->getPosition();
       DWORD pid = this->dwProcessId_;
       FloatSetObj ^c = gcnew FloatSetObj(this->x_, this->y_, this->z_, this->h_);
       SnapShot *sh = new SnapShot(pid);
       this->process_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
       int cnt = sh->searchAndSnap(c, FALSE, this->process_, 0);

       ::SendMessage(this->hWnd_, WM_KEYDOWN, VK_UP, 0);
       Sleep(200);
       ::SendMessage(this->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
       Sleep(200);
       ::SendMessage(this->hWnd_, WM_KEYUP, VK_UP, 0);
       ::SendMessage(this->hWnd_, WM_KEYUP, VK_RIGHT, 0);
       this->getPosition();

       c = gcnew FloatSetObj(this->x_, this->y_, this->z_, this->h_);
       MemBuffer *first = sh->data_;

       while (first != NULL) {
         // first->addr_
         char buf[255];
         SIZE_T lpRead;
         if (ReadProcessMemory( this->process_, first->addr_, buf, sizeof(struct ToonPos), &lpRead)) {
           struct ToonPos *tp = (struct ToonPos *) &buf[0];
           if (c->cmp(&buf[0])) {
             this->base_ = first->addr_;
             delete sh;
             return;
           }
         }
    
         first = first->next_;
       }

       this->base_ = 0;
       delete sh;
     } while (this->base_ == 0);
   }
 };

System::Void Form1::findbase_Click(System::Object^  sender, System::EventArgs^  e) {
  pi_->findbase();
}

/**
 * For each toontown window, we have some useful bits of info that we
 * want to gather
 */
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
  DWORD dwProcessId;
  HINSTANCE hInstance;
  HANDLE processHandle;
  NTSTATUS status;
  PSYSTEM_HANDLE_INFORMATION handleInfo;
  ULONG handleInfoSize = 0x10000;
  ULONG i;
  char Str[255];

  if (!hWnd)
    return TRUE;		// Not a window

  if (!::IsWindowVisible(hWnd))
    return TRUE;		// Not visible

  GetClassName(hWnd, Str, sizeof(Str)); // Probably not toontown
  if (strcmp(Str, "WinGraphicsWindow0")) 
    return TRUE;

  hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
  (void) GetWindowThreadProcessId(hWnd, &dwProcessId);

  if (!(processHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, dwProcessId))) 
    return TRUE;

  handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);

  /* NtQuerySystemInformation won't give us the correct buffer size, 
     so we guess by doubling the buffer size. */
  while ((status = NtQuerySystemInformation(SystemHandleInformation, handleInfo, handleInfoSize, NULL)) == STATUS_INFO_LENGTH_MISMATCH)
    handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize *= 2);

  /* NtQuerySystemInformation stopped giving us STATUS_INFO_LENGTH_MISMATCH. */
  if (!NT_SUCCESS(status)) {
    free(handleInfo);
    return TRUE;
  }

  for (i = 0; i < handleInfo->HandleCount; i++) {
    SYSTEM_HANDLE handle = handleInfo->Handles[i];
    HANDLE dupHandle = NULL;
    POBJECT_TYPE_INFORMATION objectTypeInfo;
    PVOID objectNameInfo;
    UNICODE_STRING objectName;
    ULONG returnLength;

    /* Check if this handle belongs to the PID the user specified. */
    if (handle.ProcessId != dwProcessId)
      continue;

    /* Duplicate the handle so we can query it. */
    if (!NT_SUCCESS(NtDuplicateObject(processHandle, (HANDLE) handle.Handle, GetCurrentProcess(), &dupHandle, 0, 0, 0))) 
      continue;

    /* Query the object type. */
    objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(0x1000);

    if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectTypeInformation, objectTypeInfo, 0x1000, NULL))) {
      free(objectTypeInfo);
      CloseHandle(dupHandle);
      continue;
    }

    if ((handle.GrantedAccess == 0x0012019f) || (handle.GrantedAccess == 0x00120189)) {
      /* We have the type, so display that. */
      free(objectTypeInfo);
      CloseHandle(dupHandle);
      continue;
    }

    objectNameInfo = malloc(0x1000);
    if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectNameInformation, objectNameInfo, 0x1000, &returnLength))) {
      /* Reallocate the buffer and try again. */
      objectNameInfo = realloc(objectNameInfo, returnLength);
      if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectNameInformation, objectNameInfo, returnLength, NULL))) {
        free(objectTypeInfo);
        free(objectNameInfo);
        CloseHandle(dupHandle);
        continue;
      }
    }

    /* Cast our buffer into an UNICODE_STRING. */
    objectName = *(PUNICODE_STRING)objectNameInfo;

    /* Print the information! */
    if (objectName.Length) {
      /* The object has a name. */
      char *n = UnicodeToUtf8(objectTypeInfo->Name.Buffer);
      if (strcmp(n, "File") == 0) {
        char *v = UnicodeToUtf8(objectName.Buffer);
        int slen = strlen(v);
        if (v[slen-3] == 'l' && v[slen-2] == 'o' && v[slen-1] == 'g') {
          const char *p = &v[slen - 4];
          while (*p != '\\' && p > v)
            p--;
          p++;
          if (strncmp(p, "toontown", 8) == 0) {
            char logFile[255];
            NormalizeFileName(v, logFile);

            // Scan the log file and find what toon the player is running on
            // that executable
            char toonName[1000];

            FILE *fp = fopen(logFile, "r");
            while (fgets(Str, sizeof(Str), fp) != NULL) {
              if (strlen(Str) < 60)
                continue;
              char *oset = &Str[21];
              if (strncmp(oset, "OTPClientRepository: Chose avatar name:", 39) == 0) {
                strcpy(toonName, &oset[40]);
                toonName[strlen(toonName) - 1 ] = '\0';
                break;
              }
            }
            fclose(fp);

            // Add it to our Window picker
            Form1::WindowPicker_->Items->Add(gcnew ToonState(gcnew String(toonName), dwProcessId, hWnd, logFile, Form1::defaultpc_));

            i = handleInfo->HandleCount;
          }
        }
        free((void *)v);
      }
      free((void *)n);
    } // if (objectName.Length)

    free(objectTypeInfo);
    free(objectNameInfo);
    CloseHandle(dupHandle);
  } // for (i = 0; i < handleInfo->HandleCount; i++)

  free(handleInfo);
  CloseHandle(processHandle);

  return TRUE;
}

void Form1::savePonds(bool interactive) {
  Stream ^fs = nullptr;

  if (interactive) {
    SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();

    saveFileDialog1->Filter = "Saved plans|*.fish|All files (*.*)|*.*";
    saveFileDialog1->CreatePrompt = true;

    if ( saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK ) {
      fs = saveFileDialog1->OpenFile();
      defaultFile_ = saveFileDialog1->FileName;
    } else
      return;
  } else 
    fs = gcnew FileStream ( defaultFile_, FileMode::Create );

  BinaryFormatter^ formatter = gcnew BinaryFormatter();
  try {
    formatter->Serialize( fs, ponds_ );
  } catch ( SerializationException^  ) {
    // Console::WriteLine( "Failed to serialize. Reason: {0}", e->Message );
    throw;
  } finally {
    fs->Close();
  }
}

void Form1::loadPonds(bool interactive) {
  Stream^ fs = nullptr;

  if (interactive) {
    OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();

    //openFileDialog1->InitialDirectory = "c:\\";
    openFileDialog1->Filter = "Saved plans|*.fish|All files (*.*)|*.*";
    openFileDialog1->FilterIndex = 0;
    openFileDialog1->CheckFileExists = true;
    //openFileDialog1->RestoreDirectory = true;

    if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK ) {
      fs = openFileDialog1->OpenFile();
      defaultFile_ = openFileDialog1->FileName;
    } else
      return;
  } else 
    fs = gcnew FileStream ( defaultFile_, FileMode::Open );

  BinaryFormatter^ formatter = gcnew BinaryFormatter;
  try {
    ponds_ = dynamic_cast<pondConfigList_t ^> (formatter->Deserialize( fs ));
  } catch ( SerializationException^  ) {
    //Console::WriteLine( "Failed to deserialize. Reason: {0}", e->Message );
    throw;
  } finally {
    fs->Close();
  }
}

void Form1::refreshWindows() {
  WindowPicker->BeginUpdate();
  WindowPicker->Items->Clear();
  WindowPicker->ClearSelected();

  if (NtQuerySystemInformation == 0)
    NtQuerySystemInformation = (_NtQuerySystemInformation) GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation");
  if (NtDuplicateObject == 0)
    NtDuplicateObject = (_NtDuplicateObject) GetLibraryProcAddress("ntdll.dll", "NtDuplicateObject");
  if (NtQueryObject == 0)
    NtQueryObject = (_NtQueryObject) GetLibraryProcAddress("ntdll.dll", "NtQueryObject");

  EnumWindows(&EnumWindowsProc, NULL);
  WindowPicker->EndUpdate();
  this->WindowPicker->SelectedIndex = 0;
}

#include "fish.hxx"

System::Void Form1::loadPondList() {
  ponds_ = gcnew pondConfigList_t();

  for (int idx = 0; idx < (sizeof(spots_) / sizeof(spots_[0])); idx++) {
    defaultpc_ = gcnew pondConfig();
    defaultpc_->pondx_ = 150;
    defaultpc_->pondy_ = 150;
    defaultpc_->pondw_ = 700;
    defaultpc_->pondh_ = 400;
    defaultpc_->fishr_ = spots_[idx].r_;
    defaultpc_->fishg_ = spots_[idx].g_;
    defaultpc_->fishb_ = spots_[idx].b_;
    defaultpc_->fisht_ = spots_[idx].tol_;
    if (this->dockradio1->Checked) {
      defaultpc_->description_ = gcnew String(spots_[idx].district_) + "-" + gcnew String(spots_[idx].pond_) + "-dock 1";
      defaultpc_->dockx_ = (float)spots_[idx].pondx1_;
      defaultpc_->docky_ = (float)spots_[idx].pondy1_;
    } if (this->dockradio2->Checked) {
      defaultpc_->description_ = gcnew String(spots_[idx].district_) + "-" + gcnew String(spots_[idx].pond_) + "-dock 2";
      defaultpc_->dockx_ = (float)spots_[idx].pondx2_;
      defaultpc_->docky_ = (float)spots_[idx].pondy2_;
    } if (this->dockradio3->Checked) {
      defaultpc_->description_ = gcnew String(spots_[idx].district_) + "-" + gcnew String(spots_[idx].pond_) + "-dock 3";
      defaultpc_->dockx_ = (float)spots_[idx].pondx3_;
      defaultpc_->docky_ = (float)spots_[idx].pondy3_;
    } if (this->dockradio4->Checked) {
      defaultpc_->description_ = gcnew String(spots_[idx].district_) + "-" + gcnew String(spots_[idx].pond_) + "-dock 4";
      defaultpc_->dockx_ = (float)spots_[idx].pondx4_;
      defaultpc_->docky_ = (float)spots_[idx].pondy4_;
    }
    defaultpc_->fisherx_ = (float)spots_[idx].fisherx_;
    defaultpc_->fishery_ = (float)spots_[idx].fishery_;
    defaultpc_->estate_ = false;
    ponds_->Add(defaultpc_);
  }


  loadCurrentPond();
  loadPonds();

}

System::Void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e) {

  SYSTEMTIME st;
  GetSystemTime(&st);
  if (st.wYear > 2013 /*|| st.wMonth > 11*/)
    exit(0);
  
  SnapShot::SetPrivilege( "SeDebugPrivilege", true);

  loadFishVectors();
  loadRaceVectors();

  loadPondList();

  WindowPicker_  = this->WindowPicker;
  refreshWindows();
  hDC_ = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
 
  this->GolfHole->Items->Clear();
  for (int idx = 0; idx < (sizeof(holes_) / sizeof(holes_[0])); idx++) 
    this->GolfHole->Items->Add(gcnew String(holes_[idx].name_));
  this->GolfHole->SelectedIndex = 0;
}

System::Void Form1::plansList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_ = this->ponds_[this->plansList->SelectedIndex];
  loadCurrentPond();
  pi_->pc_ = defaultpc_;
}

System::Void Form1::loadPonds() {
  this->plansList->Items->Clear();
  int len = this->ponds_->Count;
  for (int i = 0; i < len; i++) { 
    pondConfig ^pc = this->ponds_[i];
    this->plansList->Items->Add(pc->description_);
  }
}

System::Void Form1::refreshWindowsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
  refreshWindows();
}

void Form1::resetScale() {
  RECT r;

  r.top = 0;
  r.left = 0;
  r.bottom = 1000;
  r.right = 1000 ;
  int ret = AdjustWindowRect(&r, WS_THICKFRAME | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, false);

  pi_->deltax_ = -r.left;
  pi_->deltay_ = -r.top;

  ::GetWindowRect(pi_->hWnd_, &r);
  pi_->deltax_ += r.left;
  pi_->deltay_ += r.top;

  ::GetClientRect(pi_->hWnd_, &r);

  pi_->wx_ = r.right;
  pi_->wy_ = r.bottom;
  pi_->scalex_ = (double) r.right / 1000.0;
  pi_->scaley_ = (double) r.bottom / 1000.0;

  pi_->cast_spot_x_ = 500;
  pi_->cast_spot_y_ = 735;

  pi_->scaled_cast_spot_x_ = pi_->cast_spot_x_ * pi_->scalex_;
  pi_->scaled_cast_spot_y_ = pi_->cast_spot_y_ * pi_->scaley_;
  pi_->cx_ = pi_->scaled_cast_spot_x_ + pi_->deltax_;
  pi_->cy_ = pi_->scaled_cast_spot_y_ + pi_->deltay_;
  pi_->fullbucketx_ = SCALEX(509);
  pi_->fullbuckety_ = SCALEY(641);
  pi_->sellfishx_ = SCALEX(724);
  pi_->sellfishy_ = SCALEY(780);

  this->WindowShape->Text = pi_->deltax_ + ", " + pi_->deltay_ + ", " + pi_->scalex_ + ", " + pi_->scaley_;

  pi_->hdcSrc_  = ::GetDC(pi_->hWnd_);
  pi_->hdcDest_ = ::CreateCompatibleDC(pi_->hdcSrc_);

  pi_->bmi1_ = new BITMAPINFO();
  memset(pi_->bmi1_, 0, sizeof(BITMAPINFO));

  pi_->bmi1_->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  pi_->bmi1_->bmiHeader.biWidth = r.right;
  pi_->bmi1_->bmiHeader.biHeight = r.bottom;
  pi_->bmi1_->bmiHeader.biPlanes = 1;
  pi_->bmi1_->bmiHeader.biBitCount = 32;         // four 8-bit components 
  pi_->bmi1_->bmiHeader.biCompression = BI_RGB;
  pi_->bmi1_->bmiHeader.biSizeImage = r.right * r.bottom * 4;

  void *bits = 0;
  pi_->hBitmap1_ = CreateDIBSection(pi_->hdcSrc_, pi_->bmi1_, DIB_RGB_COLORS, &bits, NULL, 0x0);
  pi_->bits1_ = bits;

  pi_->bmi2_ = new BITMAPINFO();
  memset(pi_->bmi2_, 0, sizeof(BITMAPINFO));

  pi_->bmi2_->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  pi_->bmi2_->bmiHeader.biWidth = r.right;
  pi_->bmi2_->bmiHeader.biHeight = r.bottom;
  pi_->bmi2_->bmiHeader.biPlanes = 1;
  pi_->bmi2_->bmiHeader.biBitCount = 32;         // four 8-bit components 
  pi_->bmi2_->bmiHeader.biCompression = BI_RGB;
  pi_->bmi2_->bmiHeader.biSizeImage = r.right * r.bottom * 4;

  bits = 0;
  pi_->hBitmap2_ = CreateDIBSection(pi_->hdcSrc_, pi_->bmi2_, DIB_RGB_COLORS, &bits, NULL, 0x0);
  pi_->bits2_ = bits;

  pi_->hScanmap_ = ::CreateCompatibleBitmap(pi_->hdcSrc_, r.right, 1);

  System::IntPtr ptr = this->fish1->Handle;
  HWND hdl1 = (HWND) ptr.ToPointer();
  pi_->fish1_  = ::GetDC(hdl1);

  ptr = this->toonViewPanel->Handle;
  hdl1 = (HWND) ptr.ToPointer();
  pi_->toonView_  = ::GetDC(hdl1);

  ptr = this->fish2->Handle;
  HWND hdl2 = (HWND) ptr.ToPointer();
  pi_->fish2_  = ::GetDC(hdl2);
}


System::Void Form1::WindowPicker_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
  if (WindowPicker->SelectedIndex == -1)
    return;
  ToonState ^pi = (ToonState ^) WindowPicker->Items[this->WindowPicker->SelectedIndex];
  if (pi == nullptr)
    return;

  selectedpi_ = pi_ = pi;
  defaultpc_ = pi_->pc_;
  loadCurrentPond();

  resetScale();

  FlashWindow(pi->hWnd_, TRUE);
  Sleep(10);
  FlashWindow(pi->hWnd_, FALSE);
}

// Rehape the window to a size we "can fish"
System::Void Form1::ReshapeButton_Click(System::Object^  sender, System::EventArgs^  e)  {
  if (WindowPicker->SelectedIndex == -1)
    return;
  ToonState ^pi = (ToonState ^) WindowPicker->Items[this->WindowPicker->SelectedIndex];
  if (pi == nullptr)
    return;
  RECT r;

  r.top = 50;
  r.left = 50;
  r.bottom = 1000 + r.top;
  r.right = 1000 + r.left;

  int ret = AdjustWindowRect(&r, WS_THICKFRAME | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, false);

  SetWindowPos(pi->hWnd_, NULL, r.left, r.top, r.right - r.left, r.bottom - r.top, 0);
  Sleep(200);
  resetScale();
}

bool colorMatch(int sr, int sg, int sb, int tr, int tg, int tb, int tol) {
  if ((sr <= (tr - tol)) || (sr >= (tr + tol)))
    return false;
  if ((sg <= (tg - tol)) || (sg >= (tg + tol)))
    return false;
  if ((sb <= (tb - tol)) || (sb >= (tb + tol)))
    return false;
  return true;
}

// This sucks.. it is more code then the rest of the fricken strategy
// combined... we will come back and work on this when everything else
// is done
bool Form1::centerFish(HDC hdl, int &x, int &y, int deltax, int deltay) {
  int minX = -1;
  int maxX = -1;
  int minY = -1;
  int maxY = -1;

  // do a rough search for the fishing hole to find the boundries
  for (int tx = x - 20; tx < (x + 20); tx+= 2) {
    COLORREF c = GetPixel(hdl, tx + deltax, y + deltay);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (!colorMatch(r, g, b, pi_->pc_->fishr_, pi_->pc_->fishg_, pi_->pc_->fishb_, pi_->pc_->fisht_))
      continue;
    if ((minX == -1) || (tx < minX))
      minX = tx;
    if ((maxX == -1) || (tx > maxX))
      maxX = tx;
  }

  for (int ty = y - 20; ty < (y + 20); ty+= 2) {
    COLORREF c = GetPixel(hdl, x + deltax, ty + deltay);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (!colorMatch(r, g, b, pi_->pc_->fishr_, pi_->pc_->fishg_, pi_->pc_->fishb_, pi_->pc_->fisht_))
      continue;
    if ((minY == -1) || (ty < minY))
      minY = ty;
    if ((maxY == -1) || (ty > maxY))
      maxY = ty;
  }
  x  = (minX + maxX) / 2;
  y  = (minY + maxY) / 2;

  minX = -1;
  maxX = -1;
  minY = -1;
  maxY = -1;

  for (int tx = x - 20; tx < (x + 20); tx+= 2) {
    COLORREF c = GetPixel(hdl, tx + deltax, y + deltay);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (!colorMatch(r, g, b, pi_->pc_->fishr_, pi_->pc_->fishg_, pi_->pc_->fishb_, pi_->pc_->fisht_))
      continue;
    if ((minX == -1) || (tx < minX))
      minX = tx;
    if ((maxX == -1) || (tx > maxX))
      maxX = tx;
  }

  for (int ty = y - 20; ty < (y + 20); ty+= 2) {
    COLORREF c = GetPixel(hdl, x + deltax, ty + deltay);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (!colorMatch(r, g, b, pi_->pc_->fishr_, pi_->pc_->fishg_, pi_->pc_->fishb_, pi_->pc_->fisht_))
      continue;
    if ((minY == -1) || (ty < minY))
      minY = ty;
    if ((maxY == -1) || (ty > maxY))
      maxY = ty;
  }
  if ((minX == -1) || (minY == -1))
    return false;
  x  = (minX + maxX) / 2;
  y  = (minY + maxY) / 2;
  return true;
}
// test function
System::Void Form1::MoveMouse_Click(System::Object^  sender, System::EventArgs^  e) {
#if 1
  for (int y = 25; y <= 75; y += 50) 
    for (int x = -100; x <= 100; x += 50)  {
      startCast();
      doCast(x, y);
      Sleep(2000);
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_F9, 0);
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_F9, 0);
      Sleep(100);
    }
#else
  //  startCast();

  RECT rect;
  ::GetClientRect(pi_->hWnd_, &rect);

  System::IntPtr ptr = this->fish1->Handle;
  HWND hdl1 = (HWND) ptr.ToPointer();
  HDC h1  = ::GetDC(hdl1);

  ptr = this->fish2->Handle;
  HWND hdl2 = (HWND) ptr.ToPointer();
  HDC h2  = ::GetDC(hdl2);

  HGDIOBJ hOld = ::SelectObject(pi_->hdcDest_, pi_->hBitmap1_);
  int val = ::BitBlt(pi_->hdcDest_, 0, 0, rect.right, rect.bottom, pi_->hdcSrc_ , 0, 0, SRCCOPY);

  int x1 = (pi_->pc_->pondx_) * pi_->scalex_;
  int y1 = (pi_->pc_->pondy_) * pi_->scaley_;
  int x2 = (pi_->pc_->pondx_ + pi_->pc_->pondw_) * pi_->scalex_;
  int y2 = (pi_->pc_->pondy_ + pi_->pc_->pondh_) * pi_->scaley_;

  for (int x = x1; x < x2; x+= 1) {
    for (int y = y1; y < y2; y+= 1) {
      COLORREF c = GetPixel(pi_->hdcDest_, x, y);
      int r = GetRValue(c);
      int g = GetGValue(c);
      int b = GetBValue(c);
      if (!colorMatch(r, g, b, pi_->pc_->fishr_, pi_->pc_->fishg_, pi_->pc_->fishb_, pi_->pc_->fisht_))
        continue;
      int tx1 = x;
      int ty1 = y;
      centerFish(pi_->hdcDest_, x, y, 0, 0);

      ::BitBlt(h1, this->fish1->ClientRectangle.Left, this->fish1->ClientRectangle.Top, 100, 100, pi_->hdcDest_ , x - 50, y - 50, SRCCOPY);

      int tx = x;
      int ty = y;
      Sleep(100);
      ::BitBlt(pi_->hdcDest_, 0, 0, rect.right, rect.bottom, pi_->hdcSrc_, 0, 0, SRCCOPY);
      centerFish(pi_->hdcDest_, x, y, 0, 0);

      ::BitBlt(h2, this->fish2->ClientRectangle.Left, this->fish2->ClientRectangle.Top, 100, 100, pi_->hdcDest_ , x - 50, y - 50, SRCCOPY);

      this->fishLocX->Text = "" + x;
      this->fishLocY->Text = "" + y;

      this->fishXSpeed->Text = "" + (x - tx);
      this->fishYSpeed->Text = "" + (y - ty);

      x += (x - tx) * 10;
      y += (y - ty) * 10;

      int casty = (int) ((pi_->scaled_cast_spot_y_ - (y * (1000.0 / pi_->wy_))) / 2.75);
      int castx = (int) ((100.0 * (x - pi_->scaled_cast_spot_x_)) / (casty - 500.0));
      if (casty < 0)
        continue;

      //      doCast(castx, casty);
      Sleep(50);

      goto doexit;
    }
  }
doexit:
  ::SelectObject(pi_->hdcDest_, hOld);
#endif
}

// mousedown and get ready to cast
void Form1::startCast() {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_MOUSE;

  POINT pt;
  pt.x = SCALEX(500);
  pt.y = SCALEY(735);
  SetCursorPos(pt.x, pt.y);

  input[0].mi.dx = 0;
  input[0].mi.dy = 0;
  input[0].mi.mouseData = 0;
  input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  input[0].mi.time = 0;
  ::SendInput(1, input, sizeof(INPUT));

  Sleep(50);
}

void Form1::doCast(int dx, int dy) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_MOUSE;

  POINT pt;
  pt.x = SCALEX(500);
  pt.y = SCALEY(735);

  pt.x += dx;
  pt.y += dy;
  SetCursorPos(pt.x, pt.y);

  Sleep(200);

  input[0].mi.dx = 0;
  input[0].mi.dy = 0;
  input[0].mi.mouseData = 0;
  input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
  input[0].mi.time = 0;
  ::SendInput(1, input, sizeof(INPUT));
  Sleep(100);
}

int StringToInt(String ^s) {
  IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s);
  int r = atoi((char *) p.ToPointer());
  System::Runtime::InteropServices::Marshal::FreeHGlobal(p);
  return r;
}

double StringToFloat(String ^s) {
  IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s);
  double r = atof((char *) p.ToPointer());
  System::Runtime::InteropServices::Marshal::FreeHGlobal(p);
  return r;
}

void StringToBuf(String ^s, char *buf, int slen) {
  IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s);
  strncpy(buf, (char *) p.ToPointer(), slen);
  System::Runtime::InteropServices::Marshal::FreeHGlobal(p);
}

System::Void Form1::updateDone() {

}

System::Void Form1::pondDescription_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->description_ = this->pondDescription->Text;
}
System::Void Form1::pondFishR_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->fishr_ = StringToInt(this->pondFishR->Text);
}
System::Void Form1::pondFishG_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->fishg_ = StringToInt(this->pondFishG->Text);
}
System::Void Form1::pondFishB_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->fishb_ = StringToInt(this->pondFishB->Text);
}
System::Void Form1::pondFishT_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->fisht_ = StringToInt(this->pondFishT->Text);
}
System::Void Form1::pondDockX_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->dockx_ = (float) StringToFloat(this->pondDockX->Text);
}
System::Void Form1::pondDockY_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->docky_ = (float) StringToFloat(this->pondDockY->Text);
}
System::Void Form1::pondPondX_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->pondx_ = StringToInt(this->pondPondX->Text);
}
System::Void Form1::pondPondY_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->pondy_ = StringToInt(this->pondPondY->Text);
}
System::Void Form1::pondPondWidth_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->pondw_ = StringToInt(this->pondPondWidth->Text);
}
System::Void Form1::pondPondHeight_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->pondh_ = StringToInt(this->pondPondHeight->Text);
}
System::Void Form1::pondFisherX_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->fisherx_ = (float) StringToFloat(this->pondFisherX->Text);
}
System::Void Form1::pondFisherY_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->fishery_ = (float) StringToFloat(this->pondFisherY->Text);
}
System::Void Form1::pondEstate_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
  defaultpc_->estate_ = this->pondEstate->Checked;
}

System::Void Form1::loadCurrentPond() {
  this->pondDescription->Text = defaultpc_->description_;
  this->pondPondX->Text = "" + defaultpc_->pondx_;
  this->pondPondY->Text = "" + defaultpc_->pondy_;
  this->pondPondWidth->Text = "" + defaultpc_->pondw_;
  this->pondPondHeight->Text = "" + defaultpc_->pondh_;
  this->pondFishR->Text = "" + defaultpc_->fishr_;
  this->pondFishG->Text = "" + defaultpc_->fishg_;
  this->pondFishB->Text = "" + defaultpc_->fishb_;
  this->pondFishT->Text = "" + defaultpc_->fisht_;
  this->pondDockX->Text = "" + defaultpc_->dockx_;
  this->pondDockY->Text = "" + defaultpc_->docky_;
  this->pondFisherX->Text = "" + defaultpc_->fisherx_;
  this->pondFisherY->Text = "" + defaultpc_->fishery_;
  this->pondEstate->Checked = defaultpc_->estate_;
}

System::Void Form1::StartFishing_Click(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;
  for (int i = 0; i < len; i++) {
    if (!this->WindowPicker->GetItemChecked(i))
      continue;
    pi_ = (ToonState^) this->WindowPicker->Items[i];
    updateDone();
    resetScale();
    pi_->state_ = STATE_GOING_TO_DOCK;
  }

  this->fisherTimer->Enabled = false;
  this->fisherTimer->Interval = 3000;
  this->fisherTimer->Enabled = true;
}

double angleTo(double mx, double my, double dx, double dy) {
  return fmod(270 + (atan2(dy - my, dx - mx) * (180.0 / 3.1415926)), 360.0);
}

double distTo(double mx, double my, double dx, double dy) {
  return sqrt(((dx - mx) * (dx - mx)) + 
    ((dy - my) * (dy - my)));
}

float mmod(float x) {
  while ( x < -180)
    x += 360.0;
  while ( x >= 180.0)
    x -= 360.0;
  return x;
}

System::Void Form1::fisherTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;
  for (int i = 0; i < len; i++) {
    if (!this->WindowPicker->GetItemChecked(i))
      continue;
    pi_ = (ToonState^) this->WindowPicker->Items[i];
    COLORREF c = GetPixel(hDC_, (int) (pi_->sellfishx_ + 20), (int) (pi_->sellfishy_));
    bool sellfish = colorMatch(GetRValue(c), GetGValue(c), GetBValue(c), 244, 245, 184, 10);
    if (sellfish)
      pi_->state_ = STATE_SELL_FISH;

    c = GetPixel(hDC_, (int) pi_->cx_, (int) pi_->cy_);
    int cr = GetRValue(c); int cg = GetGValue(c); int cb = GetBValue(c);

    bool ondock = colorMatch(cr, cg, cb, 253, 0, 0, 5) || colorMatch(cr, cg, cb, 253, 253, 0, 5);
    if (ondock)
      pi_->state_ = STATE_ON_DOCK;

    if (pi_->state_ == STATE_ON_DOCK && !ondock) 
      pi_->state_ = STATE_GOT_FISH;

    switch (pi_->state_) {
    case STATE_ON_DOCK: {
      startCast();
      RECT rect;
      ::GetClientRect(pi_->hWnd_, &rect);

      int x1 = (int) ((pi_->pc_->pondx_) * pi_->scalex_);
      int y1 = (int) ((pi_->pc_->pondy_) * pi_->scaley_);
      int x2 = (int) ((pi_->pc_->pondx_ + pi_->pc_->pondw_) * pi_->scalex_);
      int y2 = (int) ((pi_->pc_->pondy_ + pi_->pc_->pondh_) * pi_->scaley_);
      HGDIOBJ hOld = ::SelectObject(pi_->hdcDest_, pi_->hBitmap1_);
      do {
        ::BitBlt(pi_->hdcDest_, 0, 0, rect.right, rect.bottom, pi_->hdcSrc_ , 0, 0, SRCCOPY);
        for (int x = x1; x < x2; x+= 10) {
          for (int y = y1; y < y2; y+= 10) {
            COLORREF c = GetPixel(pi_->hdcDest_, x, y);
            int r = GetRValue(c);
            int g = GetGValue(c);
            int b = GetBValue(c);
            if (!colorMatch(r, g, b, pi_->pc_->fishr_, pi_->pc_->fishg_, pi_->pc_->fishb_, pi_->pc_->fisht_))
              continue;
            centerFish(pi_->hdcDest_, x, y, 0, 0);
            ::BitBlt(pi_->fish1_, this->fish1->ClientRectangle.Left, this->fish1->ClientRectangle.Top, 100, 100, pi_->hdcDest_ , x - 50, y - 50, SRCCOPY);

            int tx = x;
            int ty = y;
            Sleep(100);
            ::BitBlt(pi_->hdcDest_, 0, 0, rect.right, rect.bottom, pi_->hdcSrc_, 0, 0, SRCCOPY);
            centerFish(pi_->hdcDest_, x, y, 0, 0);
            if ((x == -1) || (y == -1))
              continue;
            ::BitBlt(pi_->fish2_, this->fish1->ClientRectangle.Left, this->fish1->ClientRectangle.Top, 100, 100, pi_->hdcDest_ , x - 50, y - 50, SRCCOPY);
            if (abs(x - tx) > 8)
              continue;
            if (abs(y - ty) > 8)
              continue;
            this->fishLocX->Text = "" + x;
            this->fishLocY->Text = "" + y;

            this->fishXSpeed->Text = "" + (x - tx);
            this->fishYSpeed->Text = "" + (y - ty);

            x += (x - tx) * 8;
            y += (y - ty) * 8;

            int casty = (int) ((pi_->scaled_cast_spot_y_ - (y * (1000.0 / pi_->wy_))) / 2.75);
            int castx = (int) ((100.0 * (x - pi_->scaled_cast_spot_x_)) / (casty - 500.0));
            if (casty < 0)
              continue;

            doCast(castx, casty);
            goto doexit;
          }
        }
        c = GetPixel(hDC_, (int) pi_->fullbucketx_ + 20, (int) pi_->fullbuckety_ + 20);
        cr = GetRValue(c);  cg = GetGValue(c); cb = GetBValue(c);
        bool dialogUp = colorMatch(GetRValue(c), GetGValue(c), GetBValue(c), 255, 255, 190, 5);
        if (dialogUp) 
          break;
      } while(1);
      doexit:

      ::SelectObject(pi_->hdcDest_, hOld);

      POINT pt;
      pt.x = SCALEX(500);
      pt.y = SCALEY(750);
      SetCursorPos(pt.x, pt.y);

      this->fisherTimer->Enabled = false;
      this->fisherTimer->Interval = 3000;
      this->fisherTimer->Enabled = true;
    }
      break;
    case STATE_GOT_FISH: {
      INPUT input[1];

      for (int x = 0; x < 2; x++) {
        memset(input, 0, sizeof(input));

        POINT pt;
        pt.x = (int) pi_->fullbucketx_;
        pt.y = (int) pi_->fullbuckety_;
        SetCursorPos(pt.x, pt.y);
        Sleep(100);

        input[0].type = INPUT_MOUSE;
        input[0].mi.dx = 0;
        input[0].mi.dy = 0;
        input[0].mi.mouseData = 0;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        input[0].mi.time = 0;
        ::SendInput(1, input, sizeof(INPUT));
        Sleep(100);
        SetCursorPos(pt.x+3, pt.y+3);
        Sleep(100);
        input[0].type = INPUT_MOUSE;
        input[0].mi.dx = 0;
        input[0].mi.dy = 0;
        input[0].mi.mouseData = 0;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        input[0].mi.time = 0;
        ::SendInput(1, input, sizeof(INPUT));
        ///Start no beans click///
        Sleep(100);
        SetCursorPos(pt.x+3, pt.y+40);
        Sleep(100);
        input[0].type = INPUT_MOUSE;
        input[0].mi.dx = 0;
        input[0].mi.dy = 0;
        input[0].mi.mouseData = 0;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        input[0].mi.time = 0;
        ::SendInput(1, input, sizeof(INPUT));
        Sleep(100);
        SetCursorPos(pt.x+3, pt.y+40);
        Sleep(100);
        input[0].type = INPUT_MOUSE;
        input[0].mi.dx = 0;
        input[0].mi.dy = 0;
        input[0].mi.mouseData = 0;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        input[0].mi.time = 0;
        ::SendInput(1, input, sizeof(INPUT));
        ///End no beans click///
      }

      pi_->state_ = STATE_GOING_TO_SELL_FISH;
    }
      break;
    case STATE_NULL:
      break;
    case STATE_SELL_FISH:
    {
      INPUT input[1];

      for (int x = 0; x < 2; x++) {
        memset(input, 0, sizeof(input));

        POINT pt;
        pt.x = (int) pi_->sellfishx_;
        pt.y = (int) pi_->sellfishy_;
        SetCursorPos(pt.x, pt.y);
        Sleep(100);

        input[0].type = INPUT_MOUSE;
        input[0].mi.dx = 0;
        input[0].mi.dy = 0;
        input[0].mi.mouseData = 0;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        input[0].mi.time = 0;
        ::SendInput(1, input, sizeof(INPUT));
        Sleep(100);
        SetCursorPos(pt.x+3, pt.y+3);
        Sleep(100);
        input[0].type = INPUT_MOUSE;
        input[0].mi.dx = 0;
        input[0].mi.dy = 0;
        input[0].mi.mouseData = 0;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        input[0].mi.time = 0;
        ::SendInput(1, input, sizeof(INPUT));
        Sleep(100);
      }

      pi_->state_ = STATE_GOING_TO_DOCK;
    }
    break;
    case STATE_GOING_TO_SELL_FISH:
      pi_->tx_ = pi_->pc_->fisherx_;
      pi_->ty_ = pi_->pc_->fishery_;
      pi_->state_ = STATE_RUNNING;
      break;
    case STATE_GOING_TO_DOCK:
      pi_->tx_ = pi_->pc_->dockx_;
      pi_->ty_ = pi_->pc_->docky_;
      pi_->state_ = STATE_RUNNING;
      break;
    case STATE_RUNNING:
      pi_->getPosition();
      float dh = (float) angleTo(pi_->x_, pi_->y_, pi_->tx_, pi_->ty_);
      float delta = mmod(dh - pi_->h_);
      double t = fabs(delta * (4500.0 / 360.0));

      if (delta > 0.0) {
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
        Sleep((int)t);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
      } else {
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
        Sleep((int)t);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
      }
      Sleep(100);
      double dist = distTo(pi_->x_, pi_->y_, pi_->tx_, pi_->ty_) / 0.016;
      if (dist > 5000)
        break;
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
      if (dist > 400) {
        while (dist > 0) {
          Sleep(200);
          ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
          Sleep(200);
          ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
          dist -= 400;
        }
      } else if (dist > 0) {
        if ((dist < 50) && (pi_->tx_ == pi_->pc_->fisherx_) && (pi_->ty_ == pi_->pc_->fishery_))
          pi_->state_ = STATE_GOING_TO_DOCK;
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
        Sleep((int) dist);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
      }
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);

      break;
    }
  }
}

System::Void Form1::dockradio1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
  loadPondList();
}
System::Void Form1::dockradio2_CheckedChanged(System::Object^  sender, System::EventArgs^  e){
  loadPondList();
}
System::Void Form1::dockradio3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
  loadPondList();
}
System::Void Form1::dockradio4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
  loadPondList();
}
System::Void Form1::smallCourseRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::mediumCourseRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::largeCourseRadio_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}

System::Void Form1::GolfEmergencyTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
  startGolfing_Click(sender, e);
}

System::Void Form1::startGolfing_Click(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;
  for (int i = 0; i < len; i++) {
    if (!this->WindowPicker->GetItemChecked(i))
      continue;

    pi_ = (ToonState^) this->WindowPicker->Items[i];
    DWORD ret = SetFilePointer(pi_->flog_, 0, 0, FILE_END);
    updateDone();
    resetScale();
    pi_->state_ = STATE_GOING_TO_CART;
  }

  this->GolfTimer->Enabled = false;
  this->GolfTimer->Interval = 3000;
  this->GolfTimer->Enabled = true;
}

int inThePlayground(ToonState^ pi) {
  RECT rect;
  ::GetClientRect(pi->hWnd_, &rect);
  HGDIOBJ hOld = ::SelectObject(pi->hdcDest_, pi->hScanmap_);
  int val = ::BitBlt(pi->hdcDest_, 0, 0, rect.right, 1, pi->hdcSrc_ , 0, (int) (100.0 * ((double)rect.bottom / 1000.0)), SRCCOPY);
  // int val = ::BitBlt(pi->hdcDest_, 0, 0, rect.right, 1, pi->hdcSrc_ , 0, 100, SRCCOPY);
  for (int tx = 0; tx < rect.right; tx+= 1) {
    COLORREF c = GetPixel(pi->hdcDest_, tx, 0);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (colorMatch(r, g, b, 141, 226, 86, 6)) {
      ::SelectObject(pi->hdcDest_, hOld);
      return 1;
    }
  }
  ::SelectObject(pi->hdcDest_, hOld);
  return 0;
}

int onTheTrack(ToonState^ pi) {
  RECT rect;
  ::GetClientRect(pi->hWnd_, &rect);
  HGDIOBJ hOld = ::SelectObject(pi->hdcDest_, pi->hScanmap_);
  int val = ::BitBlt(pi->hdcDest_, 0, 0, rect.right, 1, pi->hdcSrc_ , 0, 40, SRCCOPY);
  for (int tx = 0; tx < rect.right; tx+= 1) {
    COLORREF c = GetPixel(pi->hdcDest_, tx, 0);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (colorMatch(r, g, b, 253, 253, 253, 3)) {
      ::SelectObject(pi->hdcDest_, hOld);
      return 1;
    }
  }
  ::SelectObject(pi->hdcDest_, hOld);
  return 0;
}

int readyToRace(ToonState^ pi) {
  RECT rect;
  ::GetClientRect(pi->hWnd_, &rect);
  HGDIOBJ hOld = ::SelectObject(pi->hdcDest_, pi->hScanmap_);
  int val = ::BitBlt(pi->hdcDest_, 0, 0, rect.right, 1, pi->hdcSrc_ , 0, (int) (920.0 * (rect.bottom / 1000.0)), SRCCOPY);
  for (int tx = 0; tx < rect.right; tx+= 1) {
    COLORREF c = GetPixel(pi->hdcDest_, tx, 0);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (colorMatch(r, g, b, 1, 203, 21, 10)) {
      ::SelectObject(pi->hdcDest_, hOld);
      return 1;
    }
  }
  ::SelectObject(pi->hdcDest_, hOld);
  return 0;
}

int endOfRace(ToonState^ pi) {
  RECT rect;
  ::GetClientRect(pi->hWnd_, &rect);
  HGDIOBJ hOld = ::SelectObject(pi->hdcDest_, pi->hScanmap_);
  int val = ::BitBlt(pi->hdcDest_, 0, 0, rect.right, 1, pi->hdcSrc_ , 0, (int) (750.0 * (rect.bottom / 1000.0)), SRCCOPY);
  for (int tx = 0; tx < rect.right; tx+= 1) {
    COLORREF c = GetPixel(pi->hdcDest_, tx, 0);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (colorMatch(r, g, b, 208, 60, 60, 10)) {
      for (tx = 0; tx < rect.right; tx+= 1) {
        COLORREF c = GetPixel(pi->hdcDest_, tx, 0);
        int r = GetRValue(c);
        int g = GetGValue(c);
        int b = GetBValue(c);
        if (colorMatch(r, g, b, 243, 179, 45, 10)) {
          ::SelectObject(pi->hdcDest_, hOld);
          return 1;
        }
      }
    }
  }
  ::SelectObject(pi->hdcDest_, hOld);
  return 0;
}

int readyToGolf(ToonState^ pi) {
  RECT rect;
  ::GetClientRect(pi->hWnd_, &rect);
  HGDIOBJ hOld = ::SelectObject(pi->hdcDest_, pi->hScanmap_);
  int val = ::BitBlt(pi->hdcDest_, 0, 0, rect.right, 1, pi->hdcSrc_ , 0, (int) (940.0 * (rect.bottom / 1000.0)), SRCCOPY);
  for (int tx = 0; tx < rect.right; tx+= 1) {
    COLORREF c = GetPixel(pi->hdcDest_, tx, 0);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (colorMatch(r, g, b, 250, 250, 250, 6)) {
      ::SelectObject(pi->hdcDest_, hOld);
      return 1;
    }
  }

  val = ::BitBlt(pi->hdcDest_, 0, 0, rect.right, 1, pi->hdcSrc_ , 0, (int) (867.0 * (rect.bottom / 1000.0)), SRCCOPY);
  for (int tx = 0; tx < rect.right; tx+= 1) {
    COLORREF c = GetPixel(pi->hdcDest_, tx, 0);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    if (colorMatch(r, g, b, 250, 250, 250, 6)) {
      ::SelectObject(pi->hdcDest_, hOld);
      return 2;
    }
  }

  ::SelectObject(pi->hdcDest_, hOld);
  return 0;
}


System::Void Form1::perfectHit() {
  GolfingHoles * h = &holes_[this->GolfHole->SelectedIndex];

  Sleep(500);
  switch(h->position_) {
  case GOLF_LEFT:
    ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
    ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
    Sleep(100);
    break;
  case GOLF_CENTER:
    break;
  case GOLF_RIGHT:
    ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
    ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
    Sleep(100);
    break;
  }
  Sleep(100);
  ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
  ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
  Sleep(500);
  if (h->center_before_hitting_) {
    ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
    ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
    Sleep(100);
  }
  if (h->aim_ != 0) {
    if (h->aim_ < 0) {
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
      Sleep(abs(h->aim_));
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
    } else {
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
      Sleep(abs(h->aim_));
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
    }
    Sleep(100);
  }
  ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
  Sleep(h->strength_);
  ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
}

System::Void Form1::GolfTap_Click(System::Object^  sender, System::EventArgs^  e) {
  ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
  ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
  Sleep(50);
  ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
  Sleep(200);
  ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
}

bool tallToon_ = false;

System::Void Form1::tallToon_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
  tallToon_ = this->tallToon->Checked;
}

int threshold = 120;
int road = 0;

System::Void Form1::roadBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  road = StringToInt(this->toonThreshold->Text);
}

System::Void Form1::toonThreshold_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  threshold = StringToInt(this->toonThreshold->Text);
}


System::Void Form1::GolfTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;
  for (int q = 0; q < len; q++) {
    if (!this->WindowPicker->GetItemChecked(q))
      continue;

    pi_ = (ToonState^) this->WindowPicker->Items[q];

    processLogs();
    int inplay = inThePlayground(pi_);

//						  this->runTo(13, 69, false, false);

    switch (pi_->state_) {
    case STATE_GOING_TO_CART:
      if (this->largeCourseRadio->Checked)  {
        pi_->tx_ = -67.255f;
        pi_->ty_ = -29.7f + (2.0f * q);
        pi_->state_ = STATE_RUNNING;
      } else if (this->mediumCourseRadio->Checked)  {
        pi_->tx_ = 27.567f + (2.0f * q);
        pi_->ty_ = -72.490f + (2.0f * q);
        pi_->state_ = STATE_RUNNING;
      } else if (this->smallCourseRadio->Checked)  {
        pi_->tx_ = 101.0f;
        pi_->ty_ = 63.0f - (2.0f * q);
        pi_->state_ = STATE_RUNNING;
      }
      break;
    case STATE_RUNNING:
    {
      pi_->getPosition();
      if (this->smallCourseRadio->Checked && pi_->y_ < -45)  {
        this->runTo(13, 69, false, false);
        break;
      } else if (this->largeCourseRadio->Checked && pi_->x_ > 35)  {
        this->runTo(70, -72, true, false);
        this->runTo(-67, -29, true, false);
        break;
      } 
      float dh = (float) angleTo(pi_->x_, pi_->y_, pi_->tx_, pi_->ty_);
      float delta = mmod(dh - pi_->h_);
      double t = fabs(delta * (4500.0 / 360.0));

      if (delta > 0.0) {
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
        Sleep((int)t);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
      } else {
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
        Sleep((int)t);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
      }
      Sleep(100);
      double dist = distTo(pi_->x_, pi_->y_, pi_->tx_, pi_->ty_) / 0.02;
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
      if (dist > 400) {
        while (dist > 0) {
          Sleep(200);
          ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
          Sleep(200);
          ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
          dist -= 400;
        }
      } else if (dist > 0) {
        pi_->state_ = STATE_AT_GOLF_MIDPOINT;
        Sleep((int) dist);
      }
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
    }
    this->GolfTimer->Enabled = false;
    this->GolfTimer->Interval = 3000;
    this->GolfTimer->Enabled = true;
    break;
    case STATE_AT_GOLF_MIDPOINT:
    {
      int len = this->WindowPicker->Items->Count;
      int i;
      for (i = 0; i < len; i++)  {
        if (!this->WindowPicker->GetItemChecked(i))
          continue;
        if (((ToonState^) this->WindowPicker->Items[i])->state_ != STATE_AT_GOLF_MIDPOINT)
          break;
      }
      if (i == len) {
        for (i = 0; i < len; i++)  {
          if (!this->WindowPicker->GetItemChecked(i))
            continue;

          pi_ = (ToonState^) this->WindowPicker->Items[i];
          pi_->state_ = STATE_READY_TO_JUMP_ON;

          if (this->largeCourseRadio->Checked)  {
            pi_->tx_ = -96;
            pi_->ty_ = -28;
          } else if (this->mediumCourseRadio->Checked)  {
            pi_->tx_ = 10.8f;
            pi_->ty_ = -95.0f;
          } else if (this->smallCourseRadio->Checked)  {
            pi_->tx_ = 132;
            pi_->ty_ = 47.8f;
          }
          for (int q = 0; q < 2; q++) {
            Sleep(300);
            pi_->getPosition();
            float dh = (float) angleTo(pi_->x_, pi_->y_, pi_->tx_, pi_->ty_);
            float delta = mmod(dh - pi_->h_);
            double t = fabs(delta * (4500.0 / 360.0));

            if ((int) t > 10) {
              if (delta > 0.0) {
                ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
                Sleep((int)t);
                ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
              } else {
                ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
                Sleep((int)t);
                ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
              }
            }
          }
        }
      }
      this->GolfTimer->Enabled = false;
      this->GolfTimer->Interval = 3000;
      this->GolfTimer->Enabled = true;
      break;
    }
    case STATE_READY_TO_JUMP_ON:
    {
      this->GolfTimer->Enabled = false;
      this->GolfTimer->Interval = 3000;
      this->GolfTimer->Enabled = true;

      int len = this->WindowPicker->Items->Count;
      for (int i = 0; i < len; i++)  {
        if (!this->WindowPicker->GetItemChecked(i))
          continue;
        pi_ = (ToonState^) this->WindowPicker->Items[i];
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
        pi_->state_ = STATE_ON_CART;
      }
    }
    return;
    case STATE_ON_CART:
      this->GolfEmergencyTimer->Enabled = false;

          if (this->largeCourseRadio->Checked)  {
            this->GolfEmergencyTimer->Interval = 15 * 60 * 1000;
          } else if (this->mediumCourseRadio->Checked)  {
            this->GolfEmergencyTimer->Interval = 10 * 60 * 1000;
          } else if (this->smallCourseRadio->Checked)  {
			   if (this->perfectShots->Checked)
                  this->GolfEmergencyTimer->Interval = 4 * 60 * 1000;
			   else
			     this->GolfEmergencyTimer->Interval = 6 * 60 * 1000;
          }

      this->GolfEmergencyTimer->Enabled = true;

      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
      pi_->state_ = STATE_GOING_TO_CART;
      break;
    case STATE_GOLFING:
    {
      if (inplay == 1)
        pi_->state_ = STATE_GOING_TO_CART;
      if (this->perfectShots->Checked) {
        doGolfScan();
        if (readyToGolf(pi_) == 0)
          break;
        if (pi_->firstHit_) {
          perfectHit();
          pi_->firstHit_ = false;
        } else {
          ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
          ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
          Sleep(50);
          ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
          Sleep(200);
          ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
        }
      } else {
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
        Sleep(50);
          
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
        int d = StringToInt(this->golfDelay->Text);
        if (d != 0)  
          Sleep(d);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
      }
    }
    break;
    }
  }
}

System::Void Form1::StillGolfing_Click(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;
  for (int i = 0; i < len; i++) {
    if (!this->WindowPicker->GetItemChecked(i))
      continue;

    pi_ = (ToonState^) this->WindowPicker->Items[i];
    updateDone();
    resetScale();
    pi_->state_ = STATE_GOLFING;
  }
  this->GolfTimer->Enabled = false;
  this->GolfTimer->Interval = 3000;
  this->GolfTimer->Enabled = true;
}

System::Void Form1::PerfectHit_Click(System::Object^  sender, System::EventArgs^  e) {
  perfectHit();
}

System::Void Form1::GolfMiss_Click(System::Object^  sender, System::EventArgs^  e) {
  ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
  ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
  Sleep(50);
  ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
  ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
}

System::Void Form1::processLogs() {
  char buf[8000];
  DWORD nBytesRead = 0;
  BOOL bResult = ReadFile(pi_->flog_, buf, sizeof(buf), &nBytesRead, NULL);

  // Check for eof.
  if (bResult &&  nBytesRead == 0) 
    return;

  if (strstr(buf, "DistributedGolfCourse") != NULL) 
    pi_->state_ = STATE_GOLFING;
  if (strstr(buf, "GOLF COURSE DELETE") != NULL)
    if (pi_->state_ == STATE_GOLFING)
      pi_->state_ = STATE_GOING_TO_CART;
}

System::Void Form1::startScanner_Click(System::Object^  sender, System::EventArgs^  e) {
  this->RaceTimer->Enabled = false;
  this->RaceTimer->Interval = 200;
  this->RaceTimer->Enabled = true;
}


System::Void Form1::doGolfScan() {
  RECT rect;
  ::GetClientRect(pi_->hWnd_, &rect);
  double f[100];
  int fcnt = 0;

  HGDIOBJ hOld = ::SelectObject(pi_->hdcDest_, pi_->hScanmap_);
  int val = ::BitBlt(pi_->hdcDest_, 0, 0, rect.right, 1, pi_->hdcSrc_ , 0, (int) (144.0 * (rect.bottom / 1000.0)), SRCCOPY);

  String ^pat = gcnew String("0");

  bool matched = false;
  int idx = 0;
  for (int tx = 0; tx < rect.right; tx+= 1) {
    COLORREF c = GetPixel(pi_->hdcDest_, tx, 0);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    bool match = colorMatch(r, g, b, 251, 204, 102, 5);
    if (match && !matched) {
      matched = match;
      idx = tx;
    } else if (!match && matched) {
      matched = match;
      double v = (double) ((tx + idx) / 2) / (double) rect.right;
      pat = pat + ", " + v;
      f[fcnt++] = v;
    }
  }
  ::SelectObject(pi_->hdcDest_, hOld);
  if (fcnt == 0)
    return;
  this->scanResults->Text = pat;
  fishVector fv;
  fv.setV(fcnt, f);
  int best = -1;
  double bestd = 0;
  for (int idx = 0; idx < 11; idx++) {
    double d = fv.distance(vectors[idx]);
    if (best == -1 || d < bestd) {
      best = idx;
      bestd = d;
    }
  }
  this->GolfHole->SelectedIndex = best;

  int len = this->WindowPicker->Items->Count;
  for (int i = 0; i < len; i++)  {
    ToonState^pi = (ToonState^) this->WindowPicker->Items[i];
    pi->firstHit_ = true;
  }
}

System::Void Form1::ScanButton_Click(System::Object^  sender, System::EventArgs^  e) {
  doGolfScan();
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
  // Enabling Windows XP visual effects before any controls are created
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false); 

  // Create the main window and run it
  Application::Run(gcnew Form1());
  return 0;
}


#define MIN3(x,y,z)  ((y) <= (z) ? ((x) <= (y) ? (x) : (y)) : ((x) <= (z) ? (x) : (z)))
#define MAX3(x,y,z)  ((y) >= (z) ? ((x) >= (y) ? (x) : (y)) : ((x) >= (z) ? (x) : (z)))
#define GETPIXEL(_s, _x, _y) (((unsigned char *) _s)[(_x + (_y * rect.right)) * 4])

void Form1::turnTo(int direction) {
  switch (direction) {
  case 0: {
    if (pi_->rstate_ == 1)  {
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
    } else if (pi_->rstate_ == 2)  {
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
    }
    pi_->rstate_ = 0;
    break;
  }
  case 1: {
    if (pi_->rstate_ == 0)  {
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
    } else if (pi_->rstate_ == 2)  {
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
    }
    pi_->rstate_ = 1;
    break;
  }
  case 2: {
    if (pi_->rstate_ == 1) {
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
    } else if (pi_->rstate_ == 0)  {
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
    }
    pi_->rstate_ = 2;
    break;
  }
  }
}

System::Void Form1::grabScreen(RECT &rect) {
  HGDIOBJ hOld = ::SelectObject(pi_->hdcDest_, pi_->hBitmap1_);
  int val = ::BitBlt(pi_->hdcDest_, 0, 0, rect.right, rect.bottom, pi_->hdcSrc_ , 0, 0, SRCCOPY);
  ::SelectObject(pi_->hdcDest_, hOld);

  unsigned char *src =  &GETPIXEL(pi_->bits1_, 0, 0);
  unsigned char *dest = &GETPIXEL(pi_->bits2_, 0, 0);
  int imax = rect.right * rect.bottom;
  for (int idx = 0; idx < imax; idx++) {
    unsigned char rgb_min = MIN3(src[0], src[1], src[2]);
    unsigned char rgb_max = MAX3(src[0], src[1], src[2]);
    unsigned char sat = (rgb_max == 0) ? 0 : (255*(rgb_max - rgb_min)/rgb_max);

    if (threshold == 0) {
      dest[0] = sat;
      dest[1] = sat;
      dest[2] = sat;
      dest[3] = 0;
    } else {
      if (sat > threshold) {
        dest[0] = 255;
        dest[1] = 255;
        dest[2] = 255;
        dest[3] = 0;
      } else {
        dest[0] = 0;
        dest[1] = 0;
        dest[2] = 0;
        dest[3] = 0;
      }
    }
    src += 4;
    dest += 4;
  }
}

int Form1::vscan(int middlev, int bottom, int top, RECT &rect) {
  for (int vpx = middlev - 3; vpx < middlev + 3; vpx++) {
    for (int vp = bottom; vp < top; vp++) {
      unsigned char *p = &GETPIXEL(pi_->bits2_, vpx, vp);
      if (p[0] != road) 
        return vp;
      p[0] = 0;
      p[2] = 127;
    }
  }
  return top;
}

int Form1::hscan(int middleh, int startx, int endx, int delta, RECT &rect) {
  for (int lp = startx; (delta > 0) ? (lp < endx) : (lp > endx); lp += delta) {
    unsigned char *p = &GETPIXEL(pi_->bits2_, lp, middleh);
    if (p[0] != road)  
      return lp;
    p[0] = 0;
    p[1] = 127;
  }
  return endx;
}

double Form1::countroad(int startx, int starty, int width, int height, RECT &rect) {
  double r = 0;
  for (int y = starty; y < (starty + height); y++) {
    for (int x = startx; x < (startx + width); x++) {
      unsigned char *p = &GETPIXEL(pi_->bits2_, x, y);
      if (p[0] == road)  
        r += 1;
      p[2] = 127;
    }
  }
  return r / (double) (width * height);
}

System::Void Form1::racetick() {
  if (pi_->state_ != STATE_RACE_RACING)
    return;

  RECT rect;
  ::GetClientRect(pi_->hWnd_, &rect);

  grabScreen(rect);

  int middlev = rect.right / 2;
  int toph;
  if (this->rusticRadio->Checked)
    toph = (int) ((double)rect.bottom * 0.80);
  else if (this->screwballRadio->Checked)
    toph = (int) ((double)rect.bottom * 0.70);
  else
    toph = (int) ((double)rect.bottom * 0.60);
  int middleh = (int) ((double)rect.bottom * (this->tallToon->Checked ? 0.36 : 0.35));
  int checkh = (int) ((double)rect.bottom * (this->tallToon->Checked ? 0.35 : 0.30));

  int ret = vscan(middlev, checkh, toph, rect);
  int lp = hscan(ret - 5, middlev - 5, 1, -1, rect);
  int rp = hscan(ret - 5, middlev + 5, rect.right, 1, rect);

  {
    int deltax = (int) ((double)rect.right * 0.1);
    int deltay = (int) ((double)rect.bottom * 0.1);
    double lb;
    double rb;
    if (this->cityRadio->Checked) {
      lb = countroad((int) (middlev - (deltax * 4)), middleh - deltay, (int) (deltax * 3.5), deltay * 3, rect);
      rb = countroad((int) (middlev + (deltax * 0.5)), middleh - deltay, (int) (deltax * 3.5), deltay * 3, rect);
    } else {
      lb = countroad((int) (middlev - (deltax * 3)), middleh - deltay, (int) (deltax * 2.5), deltay * 2, rect);
      rb = countroad((int) (middlev + (deltax * 0.5)), middleh - deltay, (int) (deltax * 2.5), deltay * 2, rect);
    }

    if (lb < 0.3) lb = 0;
    if (rb < 0.3) rb = 0;

    if (lb != 0 || rb != 0) {
      if (lb > rb) {
        pi_->tleft_ = 1;
        pi_->tright_ = 0;
      } else {
        pi_->tleft_ = 0;
        pi_->tright_ = 1;
      }
    }
  }

  int m = ((rp + lp) / 2);

  int direction;

  if (m < (middlev - 20)) {
    direction = 0;
  } else if (m > (middlev + 20)) { 
    direction = 2;
  } else {
    direction = 1;
  }

  pi_->cycle_ += 1;
  
  HGDIOBJ hOld = ::SelectObject(pi_->hdcDest_, pi_->hBitmap1_);
  {
    COLORREF c = GetPixel(pi_->hdcDest_, 44, 463);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    pi_->second_ = colorMatch(r, g, b, 242, 242, 0, 8);
  }

  if (pi_->cycle_ > 0) {
 
    COLORREF c = GetPixel(pi_->hdcDest_, 548, 29);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);


    if (colorMatch(r, g, b, 210, 44, 56, 10)) {
      pi_->cycle_ = -50;
      if (pi_->tleft_ == 0) {
        pi_->tleft_ = 1;
        pi_->tright_ = 0;
      } else {
        pi_->tleft_ = 0;
        pi_->tright_ = 1;
      }
    }
  }
  ::SelectObject(pi_->hdcDest_, hOld);

  if (pi_->tleft_ > pi_->tright_)  {
    this->middle->Text = "left - " + (int) pi_->tleft_ + ", " + (int) pi_->tright_;
    if (ret < middleh)  { 
      if ((pi_->cycle_ % ((this->cityRadio->Checked) ? 2 : 3)) == 0)
        direction = 0;
      else
        direction = 1;
    }
  } else {
    this->middle->Text = "right" + (int) pi_->tleft_ + ", " + (int) pi_->tright_;
    if (ret < middleh)  {
      if ((pi_->cycle_ % ((this->cityRadio->Checked) ? 2 : 3)) == 0)
        direction = 2;
      else
        direction = 1;
    }
  }

  turnTo(direction);

  if (this->bitBlit->Checked) {
    if (pi_ == (ToonState^) this->WindowPicker->Items[this->WindowPicker->SelectedIndex]) {
      HGDIOBJ hOld = ::SelectObject(pi_->hdcDest_, pi_->hBitmap2_);
      ::StretchBlt(pi_->toonView_, this->toonViewPanel->ClientRectangle.Left, this->toonViewPanel->ClientRectangle.Top,
        this->toonViewPanel->ClientRectangle.Width, this->toonViewPanel->ClientRectangle.Height, pi_->hdcDest_ , 
        0, 0, rect.right, rect.bottom, SRCCOPY);
      ::SelectObject(pi_->hdcDest_, hOld);
    }
  }
}

double Form1::distanceTo(double x, double y, bool getpos) {
  if (getpos) 
    pi_->getPosition();
  return distTo(pi_->x_, pi_->y_, x, y) / 0.016;
}

void Form1::runTo(double x, double y, bool getpos, bool nohop) {
  turnTo(x, y, getpos);
  Sleep(100);

  double dist = distanceTo(x, y, false);

  ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
  if (nohop)  
    Sleep((int) dist);
  else {
    if (dist > 400) {
      while (dist > 0) {
        Sleep(200);
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
        Sleep(200);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
        dist -= 400;
      }
    } else if (dist > 0) {
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
      Sleep((int) dist);
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
    }
  }
  ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
}

void Form1::turnTo(double x, double y, bool getpos) {
  if (getpos) {
    Sleep(300);
    pi_->getPosition();
  }

  float dh = (float) angleTo(pi_->x_, pi_->y_, x, y);
  float delta = mmod(dh - pi_->h_);
  double t = fabs(delta * (4500.0 / 360.0));

  if (delta > 0.0) {
    ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
    Sleep((int)t);
    ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
  } else {
    ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
    Sleep((int)t);
    ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
  }
}

bool Form1::runToPrelaunch(bool getpos) {
  if (getpos)
    pi_->getPosition();

  if (pi_->y_ > -60) {
    if (pi_->y_ > 20) {
      if (pi_->x_ > 0) {
        runTo(25, 13, false, true);
        return true;
      } else {
        runTo(-25, 13, false, true);
        return true;
      }
    }
    runTo(0, -24, true, true);
    runTo(0, -64, true, true);
    return true;
  }
  double x1 = 0;
  double y1 = 0;
  if (this->rusticRadio->Checked)  {
    x1 = -46; y1 = -109;
  } else if (this->screwballRadio->Checked) {
    x1 = -6; y1 = -140;
  } else {
    x1 = 47; y1 = -113;
  }
  double d1 = distanceTo(x1, y1, false);
  if (d1 > 800)  {
    runTo(x1, y1, false, false);
    return true;
  } 
  return false;
}

bool Form1::runToLaunch(int slot, bool getpos) {
  if (getpos)
    pi_->getPosition();
  double x2 = 0;
  double y2 = 0;
  double x3 = 0;
  double y3 = 0;
  if (this->rusticRadio->Checked)  {
    if (slot == 0) {
      x2 = -62.574; y2 = -107.062;
      x3 = -72.581;     y3 = -104.299;
    } else {
      x2 = -61.474; y2 = -102.576;
      x3 = -71.6;     y3 = -100.126;
    }
  } else if (this->screwballRadio->Checked) {
    if (slot == 0) {
      x2 = -7.3; y2 = -171.719;
      x3 = -8.6; y3 = -176;
    } else {
      x2 = -11.557; y2 = -171.719;
      x3 = -14.149;  y3 =  -181.605;
    }
  } else {
    if (slot == 0) {
      x2 = 63; y2 = -115;
      x3 = 73.1; y3 = -117.3;
    } else {
      x2 = 61.89; y2 = -119.3;
      x3 = 71.808; y3 = -121.8;
    }
  }
  double d2 = distanceTo(x2, y2, false);
  if (d2 > 20)  {
    runTo(x2, y2, false, true);
    turnTo(x3, y3, true);
  } else {
    turnTo(x3, y3, true);
    return false;
  }
  return true;
}

System::Void Form1::justRace_Click(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;
  for (int i = 0; i < len; i++) {
    if (!this->WindowPicker->GetItemChecked(i))
      continue;
    pi_ = (ToonState^) this->WindowPicker->Items[i];
    pi_->state_ = STATE_RACE_RACING;
  }

  this->RaceViewTimer->Enabled = false;
  this->RaceViewTimer->Interval = 50;
  this->RaceViewTimer->Enabled = true;

  this->RaceTimer->Enabled = false;
  this->RaceTimer->Interval = 200;
  this->RaceTimer->Enabled = true;
}

System::Void Form1::RunThere_Click(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;
  for (int i = 0; i < len; i++) {
    if (!this->WindowPicker->GetItemChecked(i))
      continue;
    pi_ = (ToonState^) this->WindowPicker->Items[i];
    pi_->state_ = STATE_RACE_PLAYGROUND;
  }

  this->RaceTimer->Enabled = false;
  this->RaceTimer->Interval = 200;
  this->RaceTimer->Enabled = true;
}

System::Void Form1::RaceViewTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;
  for (int i = 0; i < len; i++) {
    if (!this->WindowPicker->GetItemChecked(i))
      continue;
    pi_ = (ToonState^) this->WindowPicker->Items[i];
    racetick();
  }
}

void Form1::mouseClick(int x, int y) {
  INPUT input[1];
  memset(input, 0, sizeof(input));

  for (int q = 0; q < 2; q++) {
    POINT pt;
    pt.x = x;
    pt.y = y;
    SetCursorPos(pt.x, pt.y);
    Sleep(100);

    input[0].type = INPUT_MOUSE;
    input[0].mi.dx = 0;
    input[0].mi.dy = 0;
    input[0].mi.mouseData = 0;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    input[0].mi.time = 0;
    ::SendInput(1, input, sizeof(INPUT));
    Sleep(100);

    input[0].type = INPUT_MOUSE;
    input[0].mi.dx = 0;
    input[0].mi.dy = 0;
    input[0].mi.mouseData = 0;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    input[0].mi.time = 0;
    ::SendInput(1, input, sizeof(INPUT));
    Sleep(200);
  }
}

System::Void Form1::RaceTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;

  int slt = -1;
  for (int q = 0; q < len; q++) {
    if (!this->WindowPicker->GetItemChecked(q))
      continue;
    slt++;

    pi_ = (ToonState^) this->WindowPicker->Items[q];

    switch (pi_->state_) {
    case STATE_RACE_PAUSE:
      if (--pi_->cycle2_ > 0)
        break;
      pi_->state_ = STATE_RACE_PLAYGROUND;
      break;
    case STATE_RACE_PLAYGROUND:
      if (!runToPrelaunch(true))
        pi_->state_ = STATE_RACE_PRELAUNCH;
      break;
    case STATE_RACE_PRELAUNCH:
      if (!runToLaunch(slt, true))
        pi_->state_ = STATE_RACE_LAUNCH;
      break;
    case STATE_RACE_LAUNCH:
    {
      int len = this->WindowPicker->Items->Count;
      int i;
      for (i = 0; i < len; i++)  {
        if (!this->WindowPicker->GetItemChecked(i))
          continue;
        if (((ToonState^) this->WindowPicker->Items[i])->state_ != STATE_RACE_LAUNCH)
          break;
      }
      if (i != len)
        break;
      for (i = 0; i < len; i++)  {
        if (!this->WindowPicker->GetItemChecked(i))
          continue;
        ToonState ^p = (ToonState^) this->WindowPicker->Items[i];
        p->state_ = STATE_RACE_ONCART;
        ::SendMessage(p->hWnd_, WM_KEYDOWN, VK_UP, 0);
        ::SendMessage(p->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
      }
      Sleep(200);
      for (i = 0; i < len; i++)  {
        if (!this->WindowPicker->GetItemChecked(i))
          continue;
        ToonState ^p = (ToonState^) this->WindowPicker->Items[i];
        ::SendMessage(p->hWnd_, WM_KEYUP, VK_UP, 0);
        ::SendMessage(p->hWnd_, WM_KEYUP, VK_CONTROL, 0);
      }
    }
    break;
    case STATE_RACE_ONCART:
    {
      int oncart = doRaceScan();
      if (oncart == -1)
        break;
      bool looksgood = false;
      if (this->rusticRadio->Checked) 
        looksgood = (oncart == 4);
      else if (this->screwballRadio->Checked)
        looksgood = (oncart == 2);
      else
        looksgood = (oncart == 0);
      int my = SCALEY(638);
      int mx;
      if (looksgood)  {
        mx = SCALEX(459);
        pi_->state_ = STATE_RACE_READY_TO_RACE;
      } else {
        mx = SCALEX(540);
        pi_->state_ = STATE_RACE_PRELAUNCH;
      }
      mouseClick(mx, my);
      pi_->getPosition();
      pi_->tx_ = pi_->x_;
      pi_->ty_ = pi_->y_;
    } 
    break;
    case STATE_RACE_READY_TO_RACE:
    {
      if (inThePlayground(pi_) == 1)
        pi_->state_ = STATE_RACE_PLAYGROUND;
      else if (readyToRace(pi_) == 1) {
        mouseClick(SCALEX(880), SCALEY(920));
        pi_->state_ = STATE_RACE_RACING;
        this->RaceViewTimer->Enabled = false;
        this->RaceViewTimer->Interval = 50;
        this->RaceViewTimer->Enabled = true;
        this->emergencyTimer->Enabled = false;
        this->emergencyTimer->Interval = 12 * 60 * 1000;
        this->emergencyTimer->Enabled = true;
        if (this->onWin->Checked && (selectedpi_ == pi_)) {
          this->counterBox->Text = "" + (StringToInt(this->counterBox->Text) + 1);
        }
      }
    } 
    break;
    case STATE_RACE_RACING:
      if (inThePlayground(pi_) == 1) {
        if (++pi_->cycle3_  > 20)
          pi_->state_ = STATE_RACE_PLAYGROUND;
      } else 
        pi_->cycle3_ = 0;

      if (endOfRace(pi_) == 1) {
        bool already = true;
        for (int w = 0; w < len; w++)  {
          if (!this->WindowPicker->GetItemChecked(w))
            continue;
          ToonState ^p = (ToonState^) this->WindowPicker->Items[w];
          if (endOfRace(p) == 0){
            already = false;
            break;
          }
        }
        if (already) {
          for (int w = 0; w < len; w++)  {
            if (!this->WindowPicker->GetItemChecked(w))
              continue;
            pi_ = (ToonState^) this->WindowPicker->Items[w];
            mouseClick(SCALEX(911), SCALEY(750));
            if (this->grandPrix->Checked) {
              if (this->screwballRadio->Checked) {
                this->screwballRadio->Checked = false;
                this->rusticRadio->Checked = true;
                pi_->state_ = STATE_RACE_READY_TO_RACE;
              } else if (this->rusticRadio->Checked) {
                this->rusticRadio->Checked = false;
                this->cityRadio->Checked = true;
                pi_->state_ = STATE_RACE_READY_TO_RACE;
              } else {
                this->cityRadio->Checked = false;
                this->screwballRadio->Checked = true;
                pi_->cycle2_ = 30;
                pi_->state_ = STATE_RACE_PAUSE;
              }
            } else {
              pi_->cycle2_ = 30;
              pi_->state_ = STATE_RACE_PAUSE;
            }
          }
          return;
        }
      }

      if (--pi_->cycle2_ > 0)
        break;
        
	  
      if (pi_->rstate2_ == 0) {
        if (!this->onWin->Checked || (pi_->second_ || selectedpi_ == pi_)) {
          ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
          pi_->rstate2_ = 1;
          pi_->cycle2_ = 5;
        }
      } else { 
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
        pi_->rstate2_ = 0;

        if (this->rusticRadio->Checked) 
          pi_->cycle2_ = 1;
        else if (this->screwballRadio->Checked)
          pi_->cycle2_ = 3;
        else
          pi_->cycle2_ = 2;
      }
	  
      break;
    } // switch (pi_->state_)
  } // for (int q = 0; q < len; q++)
}

// play   3 196 27  @ 936    Hit 875, 936
// jump off cart after accepting offer to battle @ 934 950
//
// Ready to battle:
//   scan 589,500 634,500
//  ok      460,638
//  cancel  543,638

System::Void Form1::raceScanButton_Click(System::Object^  sender, System::EventArgs^  e) {
  if (WindowPicker->SelectedIndex == -1)
    return;
  ToonState ^pi = (ToonState ^) WindowPicker->Items[this->WindowPicker->SelectedIndex];
  if (pi == nullptr)
    return;

  this->raceTrack->Text = "" + doRaceScan();
}

int Form1::doRaceScan() {
  RECT rect;
  ::GetClientRect(pi_->hWnd_, &rect);
  double f[100];
  int fcnt = 0;

#define HV 1
  HGDIOBJ hOld = ::SelectObject(pi_->hdcDest_, pi_->hBitmap2_);
  int val = ::BitBlt(pi_->hdcDest_, 0, 0, rect.right, HV, pi_->hdcSrc_ , 0, (int) (500.0 * (rect.bottom / 1000.0)), SRCCOPY);

  String ^pat = gcnew String("0");
  double rs = rect.right / 1000.0;

  bool matched = false;
  int idx = 0;
  for (int tx = (int) (589.0 * rs); tx < (int) (634.0 * rs); tx+= 1) {
    COLORREF c = GetPixel(pi_->hdcDest_, tx, 0);
    int r = GetRValue(c);
    int g = GetGValue(c);
    int b = GetBValue(c);
    bool match = colorMatch(r, g, b, 252, 253, 187, 7);
    if (match && !matched) {
      matched = match;
      idx = tx;
    } else if (!match && matched) {
      matched = match;
      double v = (double) ((tx + idx) / 2) / ((634.0 - 589.0) * rs);
      pat = pat + ", " + v;
      f[fcnt++] = v;
    }
  }
  ::SelectObject(pi_->hdcDest_, hOld);
  if (fcnt == 0)
    return -1;
  this->raceScanOut->Text = pat;
  ::SelectObject(pi_->hdcDest_, hOld);

  int best = -1;
  fishVector fv;
  fv.setV(fcnt, f);
  if (this->cityRadio->Checked) {
    //double d1 = fv.distance(raceVectors[0]);
    //double d2 = fv.distance(raceVectors[1]);
    //double d3 = fv.distance(raceVectors[7]);
    double d1 = raceVectors[0].distance(fv);
    double d2 = raceVectors[1].distance(fv);
    double d3 = raceVectors[7].distance(fv);
    if (d2 < d1 && d2 < d3) 
      best = 1;
    else 
      best = 0;
  } else if (this->screwballRadio->Checked) {
    double d1 = fv.distance(raceVectors[2]);
    double d2 = fv.distance(raceVectors[3]);
    if (d1 < d2) 
      best = 2;
    else 
      best = 3;
  } else {
    double d1 = fv.distance(raceVectors[4]);
    double d2 = fv.distance(raceVectors[5]);
    double d3 = fv.distance(raceVectors[6]);
    if (d1 < d2 && d1 < d3) 
      best = 4;
    else 
      best = 5;
  }

  return best;
}

System::Void Form1::emergencyTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
  int len = this->WindowPicker->Items->Count;
  for (int q = 0; q < len; q++) {
    if (!this->WindowPicker->GetItemChecked(q))
      continue;
    pi_ = (ToonState^) this->WindowPicker->Items[q];
    pi_->state_ = STATE_RACE_PLAYGROUND;
    mouseClick(320 + pi_->deltax_, 320 + pi_->deltay_);
  }

  this->RaceTimer->Enabled = false;
  this->RaceTimer->Interval = 200;
  this->RaceTimer->Enabled = true;
}

System::Void Form1::followToonTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
  selectedpi_->getPosition();
  if (this->TrackBox->Checked) {
    this->XBox->Text = "" + selectedpi_->x_;
    this->YBox->Text = "" + selectedpi_->y_;
    this->ZBox->Text = "" + selectedpi_->z_;
    this->HBox->Text = "" + selectedpi_->h_;
  }
  int len = this->WindowPicker->Items->Count;
  for (int q = 0; q < len; q++) {
    if (!this->WindowPicker->GetItemChecked(q))
      continue;
    pi_ = (ToonState^) this->WindowPicker->Items[q];
    if (this->followToon->Checked) {
      if (selectedpi_ == pi_) 
        continue;
      pi_->getPosition();

      runTick(selectedpi_->x_, selectedpi_->y_);
    }
  }
}

System::Void Form1::runTick(double dx, double dy) {
  double dist = distanceTo(dx, dy, false);
  float dh = (float) angleTo(pi_->x_, pi_->y_, dx, dy);
  float delta = mmod(dh - pi_->h_);
  float adelta = fabs(delta);

  // pos delta is a turn to the left
  // if turnstate is 1, turning to right
  // if fturnstate is -1, turning to left

  if (delta > 0.0) {
    if (pi_->turnstate_ == 1) {
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
      pi_->turnstate_ = 0;
    }
  } else if (pi_->turnstate_ == -1) {
    ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
    pi_->turnstate_ = 0;
  }
  // if (dist >500) { amended 'to if dist ( > 30) {' and } else if (dist > 500) { amended to '} else if (dist > 500) {'  trail toon no longer loops lead toon
  // to align toons, step forward with lead toon without turning
  // when running complex route (not straight line) use lead toon to allow trail toon to follow
  // ie when running maze, run, stop, turn, run, stop, turn.  Trail toon follows with no problems on test runs.
  if (adelta > 13) {
    if (dist > 30) { 
      if (pi_->followstate_ != 0)  {
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
        pi_->followstate_ = 0;
      }
    }

    if (delta > 0.0) {
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
      pi_->turnstate_ = -1;
    } else {
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
      pi_->turnstate_ = 1;
    }
  } else if (dist > 500) {
    if (pi_->followstate_ == 0)  {
      ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_UP, 0);
      pi_->followstate_ = 1;
    }
  } else {
    if (pi_->followstate_ == 1)  {
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
      pi_->followstate_ = 0;
    }
    if (pi_->turnstate_ == 1)
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
    if (pi_->turnstate_ == -1)
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
    pi_->turnstate_ = 0;
  }
}

System::Void Form1::followToon_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
  this->followToonTimer->Enabled = false;
  this->followToonTimer->Interval = 100;
  this->followToonTimer->Enabled = this->followToon->Checked;
  if (!this->followToon->Checked) {
    if (pi_->followstate_ == 1)  {
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_UP, 0);
      pi_->followstate_ = 0;
    }
    if (pi_->turnstate_ == 1)
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_RIGHT, 0);
    if (pi_->turnstate_ == -1)
      ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_LEFT, 0);
    pi_->turnstate_ = 0;
  }
}

System::Void Form1::alignToons_Click(System::Object^  sender, System::EventArgs^  e) {
}

System::Void Form1::TrackBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
  this->followToonTimer->Enabled = false;
  this->followToonTimer->Interval = 100;
  this->followToonTimer->Enabled = this->followToon->Checked;
}
System::Void Form1::pushVals_Click(System::Object^  sender, System::EventArgs^  e) {
  selectedpi_->x_ = (float) StringToFloat(this->XBox->Text);
  selectedpi_->y_ = (float) StringToFloat(this->YBox->Text);
  selectedpi_->z_ = (float) StringToFloat(this->ZBox->Text);
  selectedpi_->h_ = (float) StringToFloat(this->HBox->Text);
  selectedpi_->putPosition();
}
System::Void Form1::XBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::YBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::ZBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::HBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}

System::Void Form1::resetMenus() {
  this->DisabledMenuItem->Checked = false;
  this->DisabledMenuItem->CheckState = System::Windows::Forms::CheckState::Unchecked;

  this->genericToolStripMenuItem->Checked = false;
  this->genericToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Unchecked;

  this->vPModeToolStripMenuItem->Checked = false;
  this->vPModeToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Unchecked;

  this->cFOModeToolStripMenuItem->Checked = false;
  this->cFOModeToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Unchecked;

  this->cJModeToolStripMenuItem->Checked = false;
  this->cJModeToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Unchecked;

  this->cEOModeToolStripMenuItem->Checked = false;
  this->cEOModeToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Unchecked;

  if (stateA_ == NULL) {
    stateA_ = new XINPUT_STATE();
    stateB_ = new XINPUT_STATE();

    LoadControllerStatus(*stateB_); 

    this->ControllerTimer->Enabled = false;
    this->ControllerTimer->Interval = 10;
    this->ControllerTimer->Enabled = true;
  }
}

System::Void Form1::genericToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
  resetMenus();
  this->genericToolStripMenuItem->Checked = true;
  this->genericToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
}
System::Void Form1::vPModeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
  resetMenus();
  this->vPModeToolStripMenuItem->Checked = true;
  this->vPModeToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
}
System::Void Form1::cFOModeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
  resetMenus();
  this->cFOModeToolStripMenuItem->Checked = true;
  this->cFOModeToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
}
System::Void Form1::cJModeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
  resetMenus();
  this->cJModeToolStripMenuItem->Checked = true;
  this->cJModeToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
}
System::Void Form1::cEOModeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
  resetMenus();
  this->cEOModeToolStripMenuItem->Checked = true;
  this->cEOModeToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
}

System::Void Form1::DisabledMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
  resetMenus();
  this->DisabledMenuItem->Checked = true;
  this->DisabledMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
}

// top ramp 2
// -5.2  -60.3
// 
// center bottom ramp
// -0.4 -132
// 
// top of ramp 1
// -5 24
// 
// getting pie
//   0, 76
// 
// bottom ramp 1
// 0 -11

int Form1::openPort(unsigned int &addr, unsigned short &port, int sender) {
  int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (fd == -1) {
    perror("socket");
    return -1;
  }

    unsigned int interf;
  struct sockaddr_in inad;


  char hostname[255];
  gethostname(hostname, sizeof(hostname));
  struct hostent* hent = gethostbyname(hostname);
  char** a = hent->h_addr_list;
  interf = *(unsigned int *) a[0];

  inad.sin_family      = AF_INET;
  if (sender) {
    inad.sin_addr.s_addr = interf;
    inad.sin_port        = 0;
  } else {
    inad.sin_addr.s_addr = htonl(INADDR_ANY);
    inad.sin_port        = htons(port);
  }

  if (bind(fd, (struct sockaddr*)&inad, sizeof(inad)) < 0) {
    perror("bind");
    return -1;
  } 

  if (!sender) {
    struct ip_mreq mr;
    mr.imr_multiaddr.s_addr = htonl(addr);
    mr.imr_interface.s_addr = interf;
    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mr,
                   sizeof(mr)) == -1)
      return -1;
  }

  return fd;
}

DWORD Form1::LoadControllerStatus(XINPUT_STATE &state) {
  memset(&state, 0, sizeof(state));
  DWORD ret = XInputGetState( 0, &state );

  if( (state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
       state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) && 
      (state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
       state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ) {     
      state.Gamepad.sThumbLX = 0;
      state.Gamepad.sThumbLY = 0;
  }

  if( (state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
       state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) && 
      (state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
       state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ) {
      state.Gamepad.sThumbRX = 0;
      state.Gamepad.sThumbRY = 0;
  }
  return ret;
}

void Form1::CheckControllerStatus(XINPUT_STATE &old, XINPUT_STATE &state)
{
#if 0
  if (state.Gamepad.sThumbLX != 0 || state.Gamepad.sThumbLY)
    LeftThumbXY(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, state);

  if (state.Gamepad.sThumbRX != 0 || state.Gamepad.sThumbRY)
    RightThumbXY(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, state);

  if (old.Gamepad.bLeftTrigger != state.Gamepad.bLeftTrigger)
    LeftTrigger(state.Gamepad.bLeftTrigger, state.Gamepad.bLeftTrigger, state);

  if (old.Gamepad.bRightTrigger != state.Gamepad.bRightTrigger)
    LeftTrigger(state.Gamepad.bRightTrigger, state.Gamepad.bRightTrigger, state);

#endif
#define CheckPad(_flag) \
  if (state.Gamepad.wButtons != old.Gamepad.wButtons) {\
    if ((state.Gamepad.wButtons & _flag) != (old.Gamepad.wButtons & _flag))\
      bool_controller((old.Gamepad.wButtons & _flag) != 0, (state.Gamepad.wButtons & _flag) != 0, state, _flag); \
  }

  CheckPad(XINPUT_GAMEPAD_DPAD_UP);
  CheckPad(XINPUT_GAMEPAD_DPAD_DOWN);
  CheckPad(XINPUT_GAMEPAD_DPAD_LEFT);
  CheckPad(XINPUT_GAMEPAD_DPAD_RIGHT);
  CheckPad(XINPUT_GAMEPAD_START);
  CheckPad(XINPUT_GAMEPAD_BACK);
  CheckPad(XINPUT_GAMEPAD_LEFT_THUMB);
  CheckPad(XINPUT_GAMEPAD_RIGHT_THUMB);
  CheckPad(XINPUT_GAMEPAD_LEFT_SHOULDER);
  CheckPad(XINPUT_GAMEPAD_RIGHT_SHOULDER);
  CheckPad(XINPUT_GAMEPAD_A);
  CheckPad(XINPUT_GAMEPAD_B);
  CheckPad(XINPUT_GAMEPAD_X);
  CheckPad(XINPUT_GAMEPAD_Y);
}

System::Void Form1::bool_controller(bool oldv, bool newv, XINPUT_STATE &state, int button) { 
  if (this->DisabledMenuItem->Checked)
    return;
  if (this->genericToolStripMenuItem->Checked) {
  } else if (this->vPModeToolStripMenuItem->Checked) {
    vp_controller(oldv, newv, state, button);
  } else if (this->cFOModeToolStripMenuItem->Checked) {
  } else if (this->cJModeToolStripMenuItem->Checked) {
  } else if (this->cEOModeToolStripMenuItem->Checked) {
  }
}

System::Void Form1::publishStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
  if (this->publishStripMenuItem1->Checked == false) {
#ifndef WINSOCK_VERSION
#define WINSOCK_VERSION MAKEWORD(2,2)
#endif

    /* Start up the windows networking */
    WSADATA wsaData;
    if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {
      printf("Initialization of windows networking failed\n");
    }

    this->publishStripMenuItem1->Checked = true;
    this->publishStripMenuItem1->CheckState = System::Windows::Forms::CheckState::Checked;

    unsigned int addr = htonl(inet_addr("239.0.10.10"));
    unsigned short port = 12345;
    fd_ = openPort(addr, port, 1);
    si_other_ = new sockaddr_in();

    memset((char *) si_other_, 0, sizeof(*si_other_));
    si_other_->sin_family = AF_INET;
    int slen = sizeof(*si_other_);
    si_other_->sin_addr.s_addr = htonl(addr);
    si_other_->sin_port = htons(port);
  }
}
System::Void Form1::ControllerTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
  LoadControllerStatus(*stateA_);
  if (memcmp(stateA_, stateB_, sizeof(*stateA_)))  {
    if (fd_ != -1) {
      int slen = sizeof(*si_other_);
      int n = sendto(fd_, (const char*) stateA_, sizeof(*stateA_), 0,
        (const sockaddr*) si_other_, slen);
    }
    CheckControllerStatus(*stateB_, *stateA_);
    memcpy(stateB_, stateA_, sizeof(*stateA_));
  }
}

System::Void Form1::VPGetPie_Click(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::VPMiddleTopRamp_Click(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::VPMiddlePlatform_Click(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::BottomRamp_Click(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::VPThrow_Click(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::VPJump_Click(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::VPBottom_Click(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::VPStandAside_Click(System::Object^  sender, System::EventArgs^  e) {
}
System::Void Form1::VPTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
}

System::Void Form1::vp_controller(bool oldv, bool newv, XINPUT_STATE &state, int button) {
  int len = this->WindowPicker->Items->Count;
  for (int q = 0; q < len; q++) {
    if (!this->WindowPicker->GetItemChecked(q))
      continue;
    pi_ = (ToonState^) this->WindowPicker->Items[q];
    switch(button) {
    case XINPUT_GAMEPAD_DPAD_UP:
    case XINPUT_GAMEPAD_DPAD_DOWN:
    case XINPUT_GAMEPAD_DPAD_LEFT:
    case XINPUT_GAMEPAD_DPAD_RIGHT:
    case XINPUT_GAMEPAD_START:
    case XINPUT_GAMEPAD_BACK:
    case XINPUT_GAMEPAD_LEFT_THUMB:
    case XINPUT_GAMEPAD_RIGHT_THUMB:
    case XINPUT_GAMEPAD_LEFT_SHOULDER:
      if (newv)  {
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_DELETE, 0);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_DELETE, 0);
      }
      break;
    case XINPUT_GAMEPAD_RIGHT_SHOULDER:
      if (newv) {
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_DELETE, 0);
        Sleep( state.Gamepad.bRightTrigger);
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_DELETE, 0);
      }
      break;
    case XINPUT_GAMEPAD_A:
    case XINPUT_GAMEPAD_B:
    case XINPUT_GAMEPAD_X:
      if (newv) 
        ::SendMessage(pi_->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
      else
        ::SendMessage(pi_->hWnd_, WM_KEYUP, VK_CONTROL, 0);
      break;
    case XINPUT_GAMEPAD_Y:
      break;
    }
  }
}
