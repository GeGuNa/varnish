..
	Copyright (c) 2021 Varnish Software AS
	SPDX-License-Identifier: BSD-2-Clause
	See LICENSE file for full text of license

Using extra digits in resp.status
=================================

In Varnish the ``.status`` variables can hold more than three
digits, which is useful to send information to ``vcl_synth{}``
about which error message to produce::

    sub vcl_recv {
       if ([...]) {
           return(synth(12404));
       }
    }

    sub vcl_synth {
        if (resp.status == 12404) {
            [...]       // this specific 404
        } else if (resp.status % 1000 == 404) {
            [...]       // all other 404's
        }
    }
