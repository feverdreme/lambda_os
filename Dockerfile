FROM archlinux

WORKDIR /app

RUN pacman -Syu --noconfirm
RUN pacman -S archlinux-keyring --noconfirm
RUN pacman -Su git base-devel --noconfirm
# RUN pacman -Su gmp libmpc mpfr --noconfirm
RUN pacman -Su nasm --noconfirm

# RUN gcc -dumpmachine

# COPY . /app

# RUN ln -s /usr/sbin/gcc /usr/sbin/i686-elf-gcc
# RUN ln -s /usr/sbin/ld /usr/sbin/i686-elf-ld
# RUN ln -s /usr/sbin/objcopy /usr/sbin/i686-elf-objcopy
# RUN make

ENV HOME=""
ENV PREFIX="$HOME/opt/cross"
ENV TARGET=i686-elf
ENV PATH="$PREFIX/bin:$PATH"

RUN echo ${PREFIX}
RUN echo ${TARGET}
RUN echo ${PATH}

# Binutils
WORKDIR $HOME/src

RUN curl https://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.xz -o binutils-2.39.tar.xz
RUN tar -xf binutils-2.39.tar.xz

WORKDIR build-binutils
RUN ../binutils-2.39/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
RUN make
RUN make install

# GCC

WORKDIR $HOME/src
# # The $PREFIX/bin dir _must_ be in the PATH. We did that above.
RUN which -- $TARGET-as || echo $TARGET-as is not in the PATH

RUN curl https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.xz -o gcc-12.2.0.tar.xz
RUN tar -xf gcc-12.2.0.tar.xz

WORKDIR build-gcc
RUN ../gcc-12.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
RUN make all-gcc
RUN make all-target-libgcc
RUN make install-gcc
RUN make install-target-libgcc

ENV PATH="$HOME/opt/cross/bin:$PATH"

# FINAL BUILD

WORKDIR /app
COPY . /app
RUN make