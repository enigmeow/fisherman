;; vtags.el
;;
;; version 0.7
;;
;; Written by Josh Siegel
;;

(setq vttag-file-names nil)
(setq vttags-list nil)
(setq vtmethod-list nil)

(defun vtinitialize-methods ()
  (message "Initializing method list...")
  (let (ptr bits)
    (setq bits (sort (mapcar 'car
      (apply 'append (mapcar '(lambda(x) (nth 3 x)) vttags-list))) 'string<))
    (setq ptr bits)
    (while (cdr ptr)
      (if (string= (car ptr) (car (cdr ptr))) 
	  (rplacd ptr (cdr (cdr ptr)))
	(setq ptr (cdr ptr))
	)
      )
    (setq vtmethod-list (mapcar 'list bits))
    )
  (message "done")
)

(defun vtgoto (class method)
 "Goto specific tag"
  (interactive (list 
		(setq vtcurrent-class 
		      (completing-read "Class: " vttags-list))
		(completing-read "Method: " 
		       (nth 3 (assoc vtcurrent-class vttags-list)))))
  (let (vtmethod-entry)
	(setq vtmethod-entry (assoc method (nth 3 (assoc class vttags-list))))
    (setq vtcurrent-class class)
    (vtgoto-file (nth 1 vtmethod-entry) (nth 2 vtmethod-entry))
    )
)


(defun vtclass (class)
  "goto a specific class"
  (interactive (list (setq vtcurrent-class 
 		      (completing-read "Class: " vttags-list))))
 (let (vtthe-line)
   (setq vtthe-line (assoc class vttags-list))
   (vtgoto-file (car (cdr vtthe-line)) 
		 (nth 2 vtthe-line))
 )
)

(defun vtreturn-method-and-class (meth)
  (list 
   (setq vtcurrent-method meth)
   (if (= (length (setq magic_list (apply 'append 
      (mapcar '(lambda(x) (if (car x) (list x) nil))
        (mapcar '(lambda(x) 
	  (list (if (assoc vtcurrent-method (nth 3 x)) (nth 0 x) nil))) 
	    vttags-list))))) 1) 
       (car (car magic_list))
       (completing-read "Class: " magic_list)
     )
   )
)

(defun vtfunction (method class)
 "Goto a method in a class"
 (interactive (vtreturn-method-and-class 
	       (completing-read "method: " vtmethod-list)))
 (vtgoto class method)
)

(defun vtinverted (method class)
 "Goto a method in a class"
 (interactive (vtreturn-method-and-class 
	       (completing-read "method: " vtmethod-list)))
 (vtgoto class method)
)

(defun vtthis (method class)
  (interactive (vtreturn-method-and-class (current-word)))
  (vtgoto class method)
)

(defun vtgoto-file (file place)
  (find-file-other-window file)
  (if (numberp place)
      (goto-char (- place 2))
    (progn
      (goto-char (point-min))
      (search-forward place)
      (beginning-of-line)
      )
  )
)


(defun vtload-tags (file)
  "Load Magic tag file"
  (interactive "fMagic tags file: ")
  (let (new_critter vtbit-o-list)
    (vtunload-tags file)
    (load file)
;    (load-file file)
    (setq new_critter (list (list 
      file (mapcar '(lambda(x) (list (car (cdr x)))) vtbit-o-list))))
  
    (if vttag-file-names
	(rplacd new_critter vttag-file-names))
  
    (setq vttag-file-names new_critter)

    (if vttags-list
	(nconc vttags-list vtbit-o-list)
        (setq  vttags-list vtbit-o-list)
    )

    (vtinitialize-methods)
  )
)

(defun vtunload-tags (file)
  "Unload loaded tags file"
  (interactive (list (completing-read "Tag file:" vttag-file-names)))
  (let (files)
    (setq files (car (cdr (assoc file vttag-file-names))))
    (if files 
	(progn
	  (setq vttags-list 
		(apply 'nconc 
		    (mapcar '(lambda(x) (if (assoc (car (cdr x)) files) nil (list x))) vttags-list)
                )
          )
	  (vtinitialize-methods)
	  (setq vttag-file-names (delq (assoc file vttag-file-names) vttag-file-names))
	)
    )
  )
)

(defun vtfile (file)
  (interactive (list (completing-read "File: " vtfiles)))
  (find-file-other-window (car (cdr (assoc file vtfiles))))
)

(defun vtdescribe-word-here nil
  (interactive)

  (setq entry (assoc (current-word) method-list))
  (message (nth 1 entry))
)

(defun vtdescribe-word nil
  (interactive)

  (vtdescribe-word-here)
  (insert last-command-char)
)

(defun vtdesc-setup  nil
  (interactive)
)

; (add-hook 'c++-mode-hook 
;    '(lambda ()
;       (define-key c++-mode-map "(" 'vtdescribe-word)
; ))
