# Building YACReader from source

YACReader and YACReaderLibrary are build using qmake. To build and install the
program, run:

> qmake-qt5 CONFIG+=[Options]
> make
> make install

from the source dir. For separate builds of YACReader or YACReaderLibrary,
enter their respective subfolders and run the commands from there.

The headless version of YACReaderLibrary is located in the YACReaderLibraryServer
folder. To build it, enter the folder and run the commands described above.


## Build dependencies:

- Qt >= 5.6 with the following modules:
	- declarative
	- quickcontrols
	- sql
	- script
	- multimedia
	- imageformats
	- opengl
	- sql-sqlite
	- network
- A pdf rendering backend (optional, see below)
- qrencode (optional)
- 7zip or p7zip (see below)
- (lib)unarr (optional, see below)

Not all dependencies are needed at build time. For example the qml components in
YACReaderLibrary (GridView, InfoView) will only show a white page if the
required qml modules (declarative, quickcontrols) are missing.
This can also happen if these dependencies are too old (i.e Qt < 5.6 is used).

## Backends

### Decompression

Configure the library you want to use throught `qmake` `CONFIG`. `CONFIG += 7zip` or `CONFIG += unarr`, if not specified `7zip` is used in MacOS and Windows and `unarr` in Linux.

#### 7zip

YACReader uses by default [7zip](https://www.7-zip.org/) for comic book archive
decompression. In MacOS and Linux, it uses [p7zip](http://p7zip.sourceforge.net/). Please read `compressed_archive/README_7zip.txt` for more details. This is the recomended library since supports a wider variety of formats, including RAR5 and 7z.

#### unarr

YACReader can use [(lib)unarr](https://github.com/selmf/unarr) for comic book archive
decompression. Most Linux distributions don't ship this library yet, so you will
probably have to build it yourself.

We recommend using (lib)unarr as a shared library, but we also support static
and embedded builds. Please consult the [README](compressed_archive/unarr/README.txt)
for more information on this topic.

### PDF

Starting with version 9.0.0 YACReader supports the following pdf render engines:

- poppler (Linux/Unix default)
- pdfium (default for Windows and MacOS)
- pdfkit (MacOS only)
- no_pdf (disable pdf support)

To override the default for a given platform add CONFIG+=[pdfbackend] as an option
when running qmake.

While the Poppler backend is well tested and has been the standard for YACReader
for a long time, it's performance is a bit lacking. The pdfium engine offers
much better performance (about 10x faster on some pdf files we tested).
However, at the time of this writing, it is not a library that is available
prepackaged for Linux.

### Other build options:

You can adjust the installation prefix as well als the path "make install" uses
to install the files.

>qmake PREFIX=DIR

sets the default prefix (for example "/", "/usr", "/usr/local").

>make install INSTALL_ROOT=DIR

can be used to install to a different location, which is usefull for packaging.

Default values:

>PREFIX=/usr
>INSTALL_ROOT=""

On embedded devices that don't support desktop OpenGL, it is recommended to use
the no_opengl config option:

qmake-qt5 CONFIG+=no_opengl

This will remove any dependency on desktop OpenGL and hardlock YACReader's
coverflow to software rendering. Please note that it does not actually remove
OpenGL from the build, the Qt toolkit will still make use of it.


# Feedback and contribution

If you're compiling YACReader because there is no package available for your
Linux distribution please consider creating and submitting a package or filing a
package request.

While we do provide packages for .deb and .rpm based distributions as well as an
AUR package for Archlinux and it's derivates, we are in need of downstream packagers
that are willing to make YACReader available as a standard package for their distro.

If you are interested, please contact @selmf on the YACReader forums or write
an email to info@yacreader.com

If you have already created a package please let us know so we can add it to
our downloads list ;)
