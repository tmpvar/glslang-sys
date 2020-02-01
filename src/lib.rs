extern "C" {
    pub fn glslang_init() -> ::std::os::raw::c_int;

    pub fn glslang_compile(
        source: *const ::std::os::raw::c_char,
        length: i32,
        stage: u32,
    ) -> ::std::os::raw::c_int;
}

pub fn compile(src: String) -> i32 {
    static mut INITIALIZED: bool = false;

    unsafe {
        if !INITIALIZED {
            glslang_init();
        }
        INITIALIZED = true;

        let r = glslang_compile(
            src.as_ptr() as *mut ::std::os::raw::c_char,
            src.len() as i32,
            4 as u32,
        );
        println!("RESULT {}", r);
        return r;
    };
}
