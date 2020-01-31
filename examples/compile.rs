extern crate glslang_sys;
use glslang_sys as glsl;

pub fn main() {
    glsl::compile("HELLO".to_string());
}
