add_rules("mode.debug", "mode.release")

-- add_cxflags("-m32")

target("clib")
    set_kind("headeronly")
    add_files("src/collections/*.h")

target("test_clib")
    set_kind("binary")
    add_files("test/main.c")
    add_deps("clib")