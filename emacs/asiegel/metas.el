(defun write-modified-files ()
  "Save all modified files."
  (interactive)
  (save-some-buffers t))

(load "compile")

(defun quiet-compile (command)
  "Call the compile command after saving all modified buffers.  This
function eliminates the annoying verification needed when compiling."
  (interactive (list (read-from-minibuffer "Compile command: "
					   compile-command nil nil
					   '(compile-history . 1))))
  (setq compile-command command)
  (save-some-buffers t nil)
  (compile-internal compile-command "No more errors"))

; These are meant for users to type
(global-set-key "\C-u" 'backward-kill-word)
(global-set-key "\M-A" 'manual-entry)
(global-set-key "\M-B" 'switch-to-buffer)
(global-set-key "\M-D" 'start-kbd-macro)
(global-set-key "\M-E" 'end-kbd-macro)
(global-set-key "\M-F" 'auto-fill-mode)
(global-set-key "\M-G" 'grep)
(global-set-key "\M-H" 'help-for-help)
(global-set-key "\M-I" 'insert-buffer)
(global-set-key "\M-J" 'recenter)
(global-set-key "\M-K" 'kill-buffer)
(global-set-key "\M-L" 'goto-line)
(global-set-key "\M-N" 'next-error)
(global-set-key "\M-O" 'quiet-compile)
(global-set-key "\M-P" nil)
(global-set-key "\M-Q" 'query-replace)
(global-set-key "\M-R" 'global-auto-revert-mode)
(global-auto-revert-mode 't)
(global-set-key "\M-S" 'write-modified-files)
(global-set-key "\M-T" 'text-mode)
(global-set-key "\M-U" 'advertised-undo)
(global-set-key "\M-V" 'describe-variable)
(global-set-key "\M-W" 'write-file)
(global-set-key "\M-X" 'call-last-kbd-macro)
(global-set-key "\M-Z" 'kill-compilation)
(global-set-key "\M-\t" 'dabbrev-expand)
(global-set-key "\M-g" 'fill-region)
(global-set-key [C-tab] 'dabbrev-expand)
(global-set-key [end] 'end-of-buffer)
(global-set-key [home] 'beginning-of-buffer)
