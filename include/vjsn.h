/*-
 * Copyright (c) 2017 Varnish Software AS
 * All rights reserved.
 *
 * Author: Poul-Henning Kamp <phk@phk.freebsd.dk>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define VJSN_TYPES \
	VJSN_TYPE_MACRO(OBJECT, object) \
	VJSN_TYPE_MACRO(ARRAY, array) \
	VJSN_TYPE_MACRO(NUMBER, number) \
	VJSN_TYPE_MACRO(STRING, string) \
	VJSN_TYPE_MACRO(TRUE, true) \
	VJSN_TYPE_MACRO(FALSE, false) \
	VJSN_TYPE_MACRO(NULL, null)

struct vjsn_val {
	unsigned		magic;
#define VJSN_VAL_MAGIC		0x08a06b80
	const char		*type;
	const char		*name;
	const char		*name_e;
	VTAILQ_ENTRY(vjsn_val)	list;
	VTAILQ_HEAD(,vjsn_val)	children;
	char			*value;
	char			*value_e;
};

struct vjsn {
	unsigned		magic;
#define VJSN_MAGIC		0x86a7f02b

	char			*raw;
	char			*ptr;
	struct vjsn_val		*value;
	const char		*err;
};

struct vjsn *vjsn_parse_end(const char *, const char *, const char **);
struct vjsn *vjsn_parse(const char *, const char **);
void vjsn_delete(struct vjsn **);
void vjsn_dump(const struct vjsn *js, FILE *fo);
void vjsn_dump_val(const struct vjsn_val *jsv, FILE *fo);
struct vjsn_val *vjsn_child(const struct vjsn_val *, const char *);

#define VJSN_TYPE_MACRO(UPPER, lower) \
	int vjsn_is_##lower(const struct vjsn_val *jsv);
VJSN_TYPES
#undef VJSN_TYPE_MACRO
