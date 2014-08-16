Leftover Items
==============

##User Interface
- [X] draw labels into `cairo_t` object for statistics graph
- [X] enable delete button
- [X] enable magnet link button
- [ ] write UI for managing system-wide settings
- [X] add "about" dialog and GtkApplication menu
- [X] enable session pause/play via headerbar button
- [ ] add DBus notification / possible bell for finished torrents
- [ ] enable running in the background (like Transmission)
- [X] enable opening multiple torrents simultaneously through file dialog

##Core
- [X] **wrapper** - asynchronous deletion of torrents after session close
- [ ] **wrapper** - support session save / resume to file
- [ ] **code** - change all `get` functions to take `const char *` rather than `char *`

##Performance and Memory
- [ ] squash all memory leak issues in Core and GLib-related functions
- [ ] increase resize performance by moving all session updates to a single GDK idle thread
