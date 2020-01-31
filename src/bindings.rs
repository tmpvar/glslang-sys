#[no_mangle]
extern "C" {
    pub fn glsl_to_spirv(source: *mut ::std::os::raw::c_char, length: u32)
        -> ::std::os::raw::c_int;
}
