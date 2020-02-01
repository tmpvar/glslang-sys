use std::path::{Path, PathBuf};
use std::{env, fs};

extern crate cc;

#[cfg(unix)]
const OS_DEPENDENT: &'static [&'static str] = &["glslang", "OSDependent", "Linux"];
#[cfg(windows)]
const OS_DEPENDENT: &'static [&'static str] = &["glslang", "OSDependent", "Windows"];

const SEARCH_DIRS: &'static [&'static [&'static str]] = &[
    &["SPIRV"],
    &[""],
    &["glslang", "Include"],
    &["glslang", "CInterface"],
    &["glslang", "GenericCodeGen"],
    &["glslang", "MachineIndependent"],
    &["glslang", "MachineIndependent", "preprocessor"],
    &["glslang", "Public"],
    OS_DEPENDENT,
    &["OGLCompilersDLL"],
];

fn main() {
    let src_root = Path::new(&env::var("CARGO_MANIFEST_DIR").unwrap()).join("glslang");
    let mut config = cc::Build::new();
    config.cpp(true);
    config.file("bindings/wrapper.cpp");

    for file in find_sources(&src_root) {
        config.file(file);
    }

    for dir in resolve_search_dirs(&src_root) {
        config.include(dir);
    }

    config.include("bindings");
    config.compile("glslang.a");
}

fn find_sources<P: AsRef<Path>>(root: &P) -> Vec<PathBuf> {
    let mut sources = Vec::new();
    for search_dir in resolve_search_dirs(root) {
        for file in fs::read_dir(search_dir).unwrap().filter_map(|e| {
            let path = e.unwrap().path();

            let mut ok = false;

            if let Some(ext) = path.extension() {
                if is_file(&path) && ext == "cpp" {
                    ok = true;
                }
            }

            if ok {
                Some(path)
            } else {
                None
            }
        }) {
            sources.push(file)
        }
    }

    sources
}

fn resolve_search_dirs<P: AsRef<Path>>(root: &P) -> Vec<PathBuf> {
    SEARCH_DIRS
        .iter()
        .map(|dir| {
            let mut buf = root.as_ref().to_owned();

            for component in *dir {
                buf.push(component)
            }

            buf
        })
        .collect()
}

fn is_file<P: AsRef<Path>>(path: &P) -> bool {
    fs::metadata(path).map(|m| m.is_file()).unwrap_or(false)
}
