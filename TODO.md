Leftover Items
==============

##User Interface
- [ ] draw labels into `cairo_t` object for statistics graph
- [ ] enable delete button
- [ ] enable magnet link button
- [ ] write UI for managing system-wide settings
- [ ] add "about" dialog and GtkApplication menu
- [ ] enable session pause/play via headerbar button
- [ ] add DBus notification / possible bell for finished torrents
- [ ] enable running in the background (like Transmission)

##Core
- [ ] **wrapper** - asynchronous deletion of torrents after session close
- [ ] **wrapper** - support session save / resume to file
- [ ] **code** - change all `get` functions to take `const char *` rather than `char *`

##Performance and Memory
- [ ] squash all memory leak issues in Core and GLib-related functions
