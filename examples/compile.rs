extern crate glslang_sys;
use glslang_sys as glsl;

pub fn main() {
    let r = glsl::compile(
        "
        layout(location=0) out vec4 colorOut;
        void main(){
            colorOut = vec4(1.0, 0.0, 0.0, 1.0);
        }"
        .to_string(),
    );
    println!("compile result: {}", r);
}
