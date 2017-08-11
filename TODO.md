Leftover Items
==============

##User Interface
- [ ] use GtkBuilder for interface
- [X] draw labels into `cairo_t` object for statistics graph
- [ ] refine/rewrite statistics graph
- [X] enable delete button
- [X] enable magnet link button
- [ ] write UI for managing system-wide settings
- [X] add "about" dialog and GtkApplication menu
- [X] enable session pause/play via headerbar button
- [X] add DBus notification / possible bell for finished torrents
- [ ] enable running in the background (like Transmission)
- [X] enable opening multiple torrents simultaneously through file dialog

##Core
- [ ] use [an actual C library](https://github.com/willemt/yabtorrent)
- [X] **wrapper** - asynchronous deletion of torrents after session close
- [ ] **wrapper** - support session save / resume to file
- [X] **code** - change all accessors to take `const char *`

##Performance and Memory
- [ ] squash all memory leak issues in Core and GLib-related functions
- [X] increase resize performance by moving all session updates to a single GDK idle thread
