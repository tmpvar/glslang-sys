extern crate glslang_sys;
use glslang_sys as glsl;

pub fn main() {
    let r = glsl::compile("asdfasdf".to_string());
    println!("compile result: {}", r);
}
