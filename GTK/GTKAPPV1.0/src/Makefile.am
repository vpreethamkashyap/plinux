## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(BGTK_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = bgtk

bgtk_SOURCES = \
	main.c \
	SettingScreen.c \
	ConfigScreen.c \
	AddConfigScreen.c \
	DelConfigScreen.c \
	AddPopup.c \
	DelPopup.c \
	MainScreen.c \
	AddDetails.c

bgtk_LDFLAGS = \
	-Wl,--export-dynamic

bgtk_LDADD = $(BGTK_LIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

