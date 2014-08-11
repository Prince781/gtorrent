# gresources
GCR	= glib-compile-resources
DEPS	= $(shell $(GCR) --generate-dependencies resources.xml)

resources.c: resources.xml $(DEPS)
	$(GCR) --generate-source resources.xml
	$(GCR) --generate-header resources.xml
