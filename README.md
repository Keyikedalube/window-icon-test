# window-icon-test
A test project for fixing synfig issue https://github.com/synfig/synfig/issues/1412

# How to build
```
git clone https://github.com/Keyikedalube/window-icon-test.git
cd window-icon-test

glib-compile-resources --generate-source window-icon-test.gresource.xml

g++ main.cpp window-icon-test.c -o window-icon-test `pkg-config gtkmm-3.0 --cflags --libs`

./window-icon-test
```
