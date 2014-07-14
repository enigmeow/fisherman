#!/bin/csh -f
set verbose

cd ~
rm -rf .subversion .cshrc .emacs .ssh .Xdefaults
ln -s repos/traders/stormbirds/other/emacs/isong/.cshrc
ln -s repos/traders/stormbirds/other/emacs/isong/.Xdefaults
