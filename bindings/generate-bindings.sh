#!/bin/bash -x -e
#
# BASE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
#
# IN="$BASE/wrapper.h"
# OUT="$BASE/bindings.rs"
#
# # bindgen "$IN"
# bindgen -o "$OUT" "$IN"
#
# sed -i '1i\
# #![allow(non_camel_case_types, non_snake_case, non_upper_case_globals)] \
# extern crate libc;
# ' "$OUT"
#
# echo '
# #[test]
# fn it_initializes_and_finalizes() {
#     unsafe {
#         ShInitialize();
#         ShFinalize();
#     }
# }' >> "$OUT"
