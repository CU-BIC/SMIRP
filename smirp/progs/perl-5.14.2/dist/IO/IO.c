/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.2210 from the
 * contents of IO.xs. Do not edit this file, edit IO.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "IO.xs"
/*
 * Copyright (c) 1997-8 Graham Barr <gbarr@pobox.com>. All rights reserved.
 * This program is free software; you can redistribute it and/or
 * modify it under the same terms as Perl itself.
 */

#define PERL_EXT_IO

#define PERL_NO_GET_CONTEXT
#include "EXTERN.h"
#define PERLIO_NOT_STDIO 1
#include "perl.h"
#include "XSUB.h"
#include "poll.h"
#ifdef I_UNISTD
#  include <unistd.h>
#endif
#if defined(I_FCNTL) || defined(HAS_FCNTL)
#  include <fcntl.h>
#endif

#ifndef SIOCATMARK
#   ifdef I_SYS_SOCKIO
#       include <sys/sockio.h>
#   endif
#endif

#ifdef PerlIO
#if defined(MACOS_TRADITIONAL) && defined(USE_SFIO)
#define PERLIO_IS_STDIO 1
#undef setbuf
#undef setvbuf
#define setvbuf		_stdsetvbuf
#define setbuf(f,b)	( __sf_setbuf(f,b) )
#endif
typedef int SysRet;
typedef PerlIO * InputStream;
typedef PerlIO * OutputStream;
#else
#define PERLIO_IS_STDIO 1
typedef int SysRet;
typedef FILE * InputStream;
typedef FILE * OutputStream;
#endif

#define MY_start_subparse(fmt,flags) start_subparse(fmt,flags)

#ifndef gv_stashpvn
#define gv_stashpvn(str,len,flags) gv_stashpv(str,flags)
#endif

#ifndef __attribute__noreturn__
#  define __attribute__noreturn__
#endif

#ifndef NORETURN_FUNCTION_END
# define NORETURN_FUNCTION_END /* NOT REACHED */ return 0
#endif

static int not_here(const char *s) __attribute__noreturn__;
static int
not_here(const char *s)
{
    croak("%s not implemented on this architecture", s);
    NORETURN_FUNCTION_END;
}


#ifndef PerlIO
#define PerlIO_fileno(f) fileno(f)
#endif

static int
io_blocking(pTHX_ InputStream f, int block)
{
#if defined(HAS_FCNTL)
    int RETVAL;
    if(!f) {
	errno = EBADF;
	return -1;
    }
    RETVAL = fcntl(PerlIO_fileno(f), F_GETFL, 0);
    if (RETVAL >= 0) {
	int mode = RETVAL;
	int newmode = mode;
#ifdef O_NONBLOCK
	/* POSIX style */

# ifndef O_NDELAY
#  define O_NDELAY O_NONBLOCK
# endif
	/* Note: UNICOS and UNICOS/mk a F_GETFL returns an O_NDELAY
	 * after a successful F_SETFL of an O_NONBLOCK. */
	RETVAL = RETVAL & (O_NONBLOCK | O_NDELAY) ? 0 : 1;

	if (block == 0) {
	    newmode &= ~O_NDELAY;
	    newmode |= O_NONBLOCK;
	} else if (block > 0) {
	    newmode &= ~(O_NDELAY|O_NONBLOCK);
	}
#else
	/* Not POSIX - better have O_NDELAY or we can't cope.
	 * for BSD-ish machines this is an acceptable alternative
	 * for SysV we can't tell "would block" from EOF but that is
	 * the way SysV is...
	 */
	RETVAL = RETVAL & O_NDELAY ? 0 : 1;

	if (block == 0) {
	    newmode |= O_NDELAY;
	} else if (block > 0) {
	    newmode &= ~O_NDELAY;
	}
#endif
	if (newmode != mode) {
	    const int ret = fcntl(PerlIO_fileno(f),F_SETFL,newmode);
	    if (ret < 0)
		RETVAL = ret;
	}
    }
    return RETVAL;
#else
#   ifdef WIN32
    char flags = (char)block;
    return ioctl(PerlIO_fileno(f), FIONBIO, &flags);
#   else
    return -1;
#   endif
#endif
}

#line 143 "IO.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
            Perl_croak(aTHX_ "Usage: %s::%s(%s)", hvname, gvname, params);
        else
            Perl_croak(aTHX_ "Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
        Perl_croak(aTHX_ "Usage: CODE(0x%"UVxf")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#ifdef PERL_IMPLICIT_CONTEXT
#define croak_xs_usage(a,b)	S_croak_xs_usage(aTHX_ a,b)
#else
#define croak_xs_usage		S_croak_xs_usage
#endif

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#line 195 "IO.c"

XS(XS_IO__Seekable_getpos); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Seekable_getpos)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)));
#line 139 "IO.xs"
	if (handle) {
#ifdef PerlIO
#if PERL_VERSION < 8
	    Fpos_t pos;
	    ST(0) = sv_newmortal();
	    if (PerlIO_getpos(handle, &pos) != 0) {
		ST(0) = &PL_sv_undef;
	    }
	    else {
		sv_setpvn(ST(0), (char *)&pos, sizeof(Fpos_t));
	    }
#else
	    ST(0) = sv_newmortal();
	    if (PerlIO_getpos(handle, ST(0)) != 0) {
		ST(0) = &PL_sv_undef;
	    }
#endif
#else
	    Fpos_t pos;
	    if (fgetpos(handle, &pos)) {
		ST(0) = &PL_sv_undef;
	    } else {
#  if PERL_VERSION >= 11
		ST(0) = newSVpvn_flags((char*)&pos, sizeof(Fpos_t), SVs_TEMP);
#  else
		ST(0) = sv_2mortal(newSVpvn((char*)&pos, sizeof(Fpos_t)));
#  endif
	    }
#endif
	}
	else {
	    errno = EINVAL;
	    ST(0) = &PL_sv_undef;
	}
#line 244 "IO.c"
    }
    XSRETURN(1);
}


XS(XS_IO__Seekable_setpos); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Seekable_setpos)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       croak_xs_usage(cv,  "handle, pos");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)));
	SV *	pos = ST(1);
	SysRet	RETVAL;
#line 179 "IO.xs"
	if (handle) {
#ifdef PerlIO
#if PERL_VERSION < 8
	    char *p;
	    STRLEN len;
	    if (SvOK(pos) && (p = SvPV(pos,len)) && len == sizeof(Fpos_t)) {
		RETVAL = PerlIO_setpos(handle, (Fpos_t*)p);
	    }
	    else {
		RETVAL = -1;
		errno = EINVAL;
	    }
#else
	    RETVAL = PerlIO_setpos(handle, pos);
#endif
#else
	    char *p;
	    STRLEN len;
	    if ((p = SvPV(pos,len)) && len == sizeof(Fpos_t)) {
		RETVAL = fsetpos(handle, (Fpos_t*)p);
	    }
	    else {
		RETVAL = -1;
		errno = EINVAL;
	    }
#endif
	}
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 296 "IO.c"
	ST(0) = sv_newmortal();
	if (RETVAL != -1) {
	    if (RETVAL == 0)
		sv_setpvn(ST(0), "0 but true", 10);
	    else
		sv_setiv(ST(0), (IV)RETVAL);
	}
    }
    XSRETURN(1);
}


XS(XS_IO__File_new_tmpfile); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__File_new_tmpfile)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 0 || items > 1)
       croak_xs_usage(cv,  "packname = \"IO::File\"");
    {
	const char *	packname;
#line 219 "IO.xs"
	OutputStream fp;
	GV *gv;
#line 324 "IO.c"

	if (items < 1)
	    packname = "IO::File";
	else {
	    packname = (const char *)SvPV_nolen(ST(0));
	}
#line 222 "IO.xs"
#ifdef PerlIO
	fp = PerlIO_tmpfile();
#else
	fp = tmpfile();
#endif
	gv = (GV*)SvREFCNT_inc(newGVgen(packname));
	if (gv)
	    (void) hv_delete(GvSTASH(gv), GvNAME(gv), GvNAMELEN(gv), G_DISCARD);
	if (gv && do_open(gv, "+>&", 3, FALSE, 0, 0, fp)) {
	    ST(0) = sv_2mortal(newRV((SV*)gv));
	    sv_bless(ST(0), gv_stashpv(packname, TRUE));
	    SvREFCNT_dec(gv);   /* undo increment in newRV() */
	}
	else {
	    ST(0) = &PL_sv_undef;
	    SvREFCNT_dec(gv);
	}
#line 349 "IO.c"
    }
    XSRETURN(1);
}


XS(XS_IO__Poll__poll); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Poll__poll)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 1)
       croak_xs_usage(cv,  "timeout, ...");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	int	timeout = (int)SvIV(ST(0));
#line 246 "IO.xs"
{
#ifdef HAS_POLL
    const int nfd = (items - 1) / 2;
    SV *tmpsv = NEWSV(999,nfd * sizeof(struct pollfd));
    struct pollfd *fds = (struct pollfd *)SvPVX(tmpsv);
    int i,j,ret;
    for(i=1, j=0  ; j < nfd ; j++) {
	fds[j].fd = SvIV(ST(i));
	i++;
	fds[j].events = (short)SvIV(ST(i));
	i++;
	fds[j].revents = 0;
    }
    if((ret = poll(fds,nfd,timeout)) >= 0) {
	for(i=1, j=0 ; j < nfd ; j++) {
	    sv_setiv(ST(i), fds[j].fd); i++;
	    sv_setiv(ST(i), fds[j].revents); i++;
	}
    }
    SvREFCNT_dec(tmpsv);
    XSRETURN_IV(ret);
#else
	not_here("IO::Poll::poll");
#endif
}
#line 395 "IO.c"
	PUTBACK;
	return;
    }
}


XS(XS_IO__Handle_blocking); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Handle_blocking)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 1 || items > 2)
       croak_xs_usage(cv,  "handle, blk=-1");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)));
	int	blk;

	if (items < 2)
	    blk = -1;
	else {
	    blk = (int)SvIV(ST(1));
	}
#line 280 "IO.xs"
{
    const int ret = io_blocking(aTHX_ handle, items == 1 ? -1 : blk ? 1 : 0);
    if(ret >= 0)
	XSRETURN_IV(ret);
    else
	XSRETURN_UNDEF;
}
#line 429 "IO.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_IO__Handle_ungetc); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Handle_ungetc)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       croak_xs_usage(cv,  "handle, c");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)));
	int	c = (int)SvIV(ST(1));
	int	RETVAL;
	dXSTARG;
#line 295 "IO.xs"
	if (handle)
#ifdef PerlIO
	    RETVAL = PerlIO_ungetc(handle, c);
#else
	    RETVAL = ungetc(c, handle);
#endif
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 461 "IO.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_IO__Handle_error); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Handle_error)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)));
	int	RETVAL;
	dXSTARG;
#line 312 "IO.xs"
	if (handle)
#ifdef PerlIO
	    RETVAL = PerlIO_error(handle);
#else
	    RETVAL = ferror(handle);
#endif
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 493 "IO.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_IO__Handle_clearerr); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Handle_clearerr)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)));
	int	RETVAL;
	dXSTARG;
#line 329 "IO.xs"
	if (handle) {
#ifdef PerlIO
	    PerlIO_clearerr(handle);
#else
	    clearerr(handle);
#endif
	    RETVAL = 0;
	}
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 527 "IO.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_IO__Handle_untaint); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Handle_untaint)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	SV *	handle = ST(0);
	int	RETVAL;
	dXSTARG;
#line 348 "IO.xs"
#ifdef IOf_UNTAINT
	IO * io;
	io = sv_2io(handle);
	if (io) {
	    IoFLAGS(io) |= IOf_UNTAINT;
	    RETVAL = 0;
	}
        else {
#endif
	    RETVAL = -1;
	    errno = EINVAL;
#ifdef IOf_UNTAINT
	}
#endif
#line 563 "IO.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS(XS_IO__Handle_flush); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Handle_flush)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	OutputStream	handle = IoOFP(sv_2io(ST(0)));
	SysRet	RETVAL;
#line 369 "IO.xs"
	if (handle)
#ifdef PerlIO
	    RETVAL = PerlIO_flush(handle);
#else
	    RETVAL = Fflush(handle);
#endif
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 594 "IO.c"
	ST(0) = sv_newmortal();
	if (RETVAL != -1) {
	    if (RETVAL == 0)
		sv_setpvn(ST(0), "0 but true", 10);
	    else
		sv_setiv(ST(0), (IV)RETVAL);
	}
    }
    XSRETURN(1);
}


XS(XS_IO__Handle_setbuf); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Handle_setbuf)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 1)
       croak_xs_usage(cv,  "handle, ...");
    {
	OutputStream	handle = IoOFP(sv_2io(ST(0)));
#line 386 "IO.xs"
	if (handle)
#ifdef PERLIO_IS_STDIO
        {
	    char *buf = items == 2 && SvPOK(ST(1)) ?
	      sv_grow(ST(1), BUFSIZ) : 0;
	    setbuf(handle, buf);
	}
#else
	    not_here("IO::Handle::setbuf");
#endif
#line 630 "IO.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_IO__Handle_setvbuf); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Handle_setvbuf)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    PERL_UNUSED_VAR(cv); /* -W */
    {
	SysRet	RETVAL;
#line 400 "IO.xs"
	if (items != 4)
            Perl_croak(aTHX_ "Usage: IO::Handle::setvbuf(handle, buf, type, size)");
#if defined(PERLIO_IS_STDIO) && defined(_IOFBF) && defined(HAS_SETVBUF)
    {
        OutputStream	handle = 0;
	char *		buf = SvPOK(ST(1)) ? sv_grow(ST(1), SvIV(ST(3))) : 0;
	int		type;
	int		size;

	if (items == 4) {
	    handle = IoOFP(sv_2io(ST(0)));
	    buf    = SvPOK(ST(1)) ? sv_grow(ST(1), SvIV(ST(3))) : 0;
	    type   = (int)SvIV(ST(2));
	    size   = (int)SvIV(ST(3));
	}
	if (!handle)			/* Try input stream. */
	    handle = IoIFP(sv_2io(ST(0)));
	if (items == 4 && handle)
	    RETVAL = setvbuf(handle, buf, type, size);
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
    }
#else
	RETVAL = (SysRet) not_here("IO::Handle::setvbuf");
#endif
#line 675 "IO.c"
	ST(0) = sv_newmortal();
	if (RETVAL != -1) {
	    if (RETVAL == 0)
		sv_setpvn(ST(0), "0 but true", 10);
	    else
		sv_setiv(ST(0), (IV)RETVAL);
	}
    }
    XSRETURN(1);
}


XS(XS_IO__Handle_sync); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Handle_sync)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	OutputStream	handle = IoOFP(sv_2io(ST(0)));
	SysRet	RETVAL;
#line 435 "IO.xs"
#ifdef HAS_FSYNC
	if(handle)
	    RETVAL = fsync(PerlIO_fileno(handle));
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#else
	RETVAL = (SysRet) not_here("IO::Handle::sync");
#endif
#line 712 "IO.c"
	ST(0) = sv_newmortal();
	if (RETVAL != -1) {
	    if (RETVAL == 0)
		sv_setpvn(ST(0), "0 but true", 10);
	    else
		sv_setiv(ST(0), (IV)RETVAL);
	}
    }
    XSRETURN(1);
}


XS(XS_IO__Socket_sockatmark); /* prototype to pass -Wmissing-prototypes */
XS(XS_IO__Socket_sockatmark)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "sock");
    {
	InputStream	sock = IoIFP(sv_2io(ST(0)));
#line 456 "IO.xs"
     int fd;
#line 739 "IO.c"
	SysRet	RETVAL;
#line 458 "IO.xs"
   {
     fd = PerlIO_fileno(sock);
#ifdef HAS_SOCKATMARK
     RETVAL = sockatmark(fd);
#else
     {
       int flag = 0;
#   ifdef SIOCATMARK
#     if defined(NETWARE) || defined(WIN32)
       if (ioctl(fd, SIOCATMARK, (void*)&flag) != 0)
#     else
       if (ioctl(fd, SIOCATMARK, &flag) != 0)
#     endif
	 XSRETURN_UNDEF;
#   else
       not_here("IO::Socket::atmark");
#   endif
       RETVAL = flag;
     }
#endif
   }
#line 763 "IO.c"
	ST(0) = sv_newmortal();
	if (RETVAL != -1) {
	    if (RETVAL == 0)
		sv_setpvn(ST(0), "0 but true", 10);
	    else
		sv_setiv(ST(0), (IV)RETVAL);
	}
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_IO); /* prototype to pass -Wmissing-prototypes */
XS(boot_IO)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
#ifdef XS_APIVERSION_BOOTCHECK
    XS_APIVERSION_BOOTCHECK;
#endif
    XS_VERSION_BOOTCHECK ;

        newXS("IO::Seekable::getpos", XS_IO__Seekable_getpos, file);
        newXS("IO::Seekable::setpos", XS_IO__Seekable_setpos, file);
        newXS("IO::File::new_tmpfile", XS_IO__File_new_tmpfile, file);
        newXS("IO::Poll::_poll", XS_IO__Poll__poll, file);
        (void)newXSproto_portable("IO::Handle::blocking", XS_IO__Handle_blocking, file, "$;$");
        newXS("IO::Handle::ungetc", XS_IO__Handle_ungetc, file);
        newXS("IO::Handle::error", XS_IO__Handle_error, file);
        newXS("IO::Handle::clearerr", XS_IO__Handle_clearerr, file);
        newXS("IO::Handle::untaint", XS_IO__Handle_untaint, file);
        newXS("IO::Handle::flush", XS_IO__Handle_flush, file);
        newXS("IO::Handle::setbuf", XS_IO__Handle_setbuf, file);
        newXS("IO::Handle::setvbuf", XS_IO__Handle_setvbuf, file);
        newXS("IO::Handle::sync", XS_IO__Handle_sync, file);
        (void)newXSproto_portable("IO::Socket::sockatmark", XS_IO__Socket_sockatmark, file, "$");

    /* Initialisation Section */

#line 483 "IO.xs"
{
    HV *stash;
    /*
     * constant subs for IO::Poll
     */
    stash = gv_stashpvn("IO::Poll", 8, TRUE);
#ifdef	POLLIN
	newCONSTSUB(stash,"POLLIN",newSViv(POLLIN));
#endif
#ifdef	POLLPRI
        newCONSTSUB(stash,"POLLPRI", newSViv(POLLPRI));
#endif
#ifdef	POLLOUT
        newCONSTSUB(stash,"POLLOUT", newSViv(POLLOUT));
#endif
#ifdef	POLLRDNORM
        newCONSTSUB(stash,"POLLRDNORM", newSViv(POLLRDNORM));
#endif
#ifdef	POLLWRNORM
        newCONSTSUB(stash,"POLLWRNORM", newSViv(POLLWRNORM));
#endif
#ifdef	POLLRDBAND
        newCONSTSUB(stash,"POLLRDBAND", newSViv(POLLRDBAND));
#endif
#ifdef	POLLWRBAND
        newCONSTSUB(stash,"POLLWRBAND", newSViv(POLLWRBAND));
#endif
#ifdef	POLLNORM
        newCONSTSUB(stash,"POLLNORM", newSViv(POLLNORM));
#endif
#ifdef	POLLERR
        newCONSTSUB(stash,"POLLERR", newSViv(POLLERR));
#endif
#ifdef	POLLHUP
        newCONSTSUB(stash,"POLLHUP", newSViv(POLLHUP));
#endif
#ifdef	POLLNVAL
        newCONSTSUB(stash,"POLLNVAL", newSViv(POLLNVAL));
#endif
    /*
     * constant subs for IO::Handle
     */
    stash = gv_stashpvn("IO::Handle", 10, TRUE);
#ifdef _IOFBF
        newCONSTSUB(stash,"_IOFBF", newSViv(_IOFBF));
#endif
#ifdef _IOLBF
        newCONSTSUB(stash,"_IOLBF", newSViv(_IOLBF));
#endif
#ifdef _IONBF
        newCONSTSUB(stash,"_IONBF", newSViv(_IONBF));
#endif
#ifdef SEEK_SET
        newCONSTSUB(stash,"SEEK_SET", newSViv(SEEK_SET));
#endif
#ifdef SEEK_CUR
        newCONSTSUB(stash,"SEEK_CUR", newSViv(SEEK_CUR));
#endif
#ifdef SEEK_END
        newCONSTSUB(stash,"SEEK_END", newSViv(SEEK_END));
#endif
}

#line 880 "IO.c"

    /* End of Initialisation Section */

#if (PERL_REVISION == 5 && PERL_VERSION >= 9)
  if (PL_unitcheckav)
       call_list(PL_scopestack_ix, PL_unitcheckav);
#endif
    XSRETURN_YES;
}

