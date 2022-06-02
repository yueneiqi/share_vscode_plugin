set_project("share_vscode_plugin")

add_rules("mode.release", "mode.debug")

-- set_warnings("all", "error")
add_ldflags(
            -- "-fsanitize=undefined",
            -- "-fsanitize=address",
            "-lfmt",
            {force = true}
            )
-- add_cxflags(
            -- "-Wall", 
            -- "-Wextra", 
            -- "-Wpedantic", 
            -- "-Werror",
            -- "-fsanitize=undefined",
            -- "-fsanitize=address",

            -- "-Wconversion",
            -- "-Wfloat-equal",
            -- "-Wformat-nonliteral",
            -- "-Wformat-security",
            -- "-Wformat-y2k",
            -- "-Wformat=2",
            -- "-Wimport",
            -- "-Winvalid-pch",
            -- "-Wlogical-op",  -- for GCC
            -- "-Wmissing-declarations",
            -- "-Wmissing-field-initializers",
            -- "-Wmissing-format-attribute",
            -- "-Wmissing-include-dirs",
            -- "-Wmissing-noreturn",
            -- "-Wpacked",
            -- "-Wpointer-arith",
            -- "-Wredundant-decls",
            -- "-Wshadow",
            -- "-Wstack-protector",
            -- "-Wstrict-null-sentinel",  -- for GCC
            -- "-Wswitch-enum",
            -- "-Wundef",
            -- "-Wwrite-strings"
            -- )

-- High Performance / Low Memory / Security                       
-- add_cxflags(
--             "-Wdisabled-optimization",
--             "-Wpadded",
--             "-Wsign-conversion",
--             "-Wsign-promo",
--             "-Wstrict-aliasing=2",
--             "-Wstrict-overflow=5",
--             "-Wunused",
--             "-Wunused-parameter"
--             )

set_languages("c++20")

includes("**/xmake.lua")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

