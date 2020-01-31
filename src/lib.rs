extern "C" {
    #[no_mangle]
    pub fn glsl_to_spirv(source: *mut ::std::os::raw::c_char, length: u32)
        -> ::std::os::raw::c_int;
}


pub fn compile(src: String) -> i32 {
    unsafe {
        let r = glsl_to_spirv(src.as_ptr() as *mut ::std::os::raw::c_char, src.len() as u32);
        println!("RESULT {}", r);
        return r;
    };
}
