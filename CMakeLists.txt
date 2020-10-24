cmake_minimum_required(VERSION 3.1...3.16)

project(NES
    VERSION 1.0
    DESCRIPTION "NES emulator written in C++."
    LANGUAGES CXX)

set(SOURCE_LIST
    main.cpp
    io/rom_file.hpp
    io/rom_file.cpp
    cpu/cpu.hpp
    cpu/cpu.cpp
    cpu/cpu_logger.hpp
    cpu/cpu_logger.cpp
    cpu/instructions/cpu_instruction_addressing_mode.hpp
    cpu/instructions/cpu_instruction_base.hpp
    cpu/instructions/cpu_instruction_base.cpp
    cpu/instructions/cpu_instruction_op_adc.hpp
    cpu/instructions/cpu_instruction_op_adc.cpp
    cpu/instructions/cpu_instruction_op_and.hpp
    cpu/instructions/cpu_instruction_op_and.cpp
    cpu/instructions/cpu_instruction_op_asl.hpp
    cpu/instructions/cpu_instruction_op_asl.cpp
    cpu/instructions/cpu_instruction_op_bcc.hpp
    cpu/instructions/cpu_instruction_op_bcc.cpp
    cpu/instructions/cpu_instruction_op_bcs.hpp
    cpu/instructions/cpu_instruction_op_bcs.cpp
    cpu/instructions/cpu_instruction_op_beq.hpp
    cpu/instructions/cpu_instruction_op_beq.cpp
    cpu/instructions/cpu_instruction_op_bit.hpp
    cpu/instructions/cpu_instruction_op_bit.cpp
    cpu/instructions/cpu_instruction_op_bmi.hpp
    cpu/instructions/cpu_instruction_op_bmi.cpp
    cpu/instructions/cpu_instruction_op_bne.hpp
    cpu/instructions/cpu_instruction_op_bne.cpp
    cpu/instructions/cpu_instruction_op_bpl.hpp
    cpu/instructions/cpu_instruction_op_bpl.cpp
    cpu/instructions/cpu_instruction_op_brk.hpp
    cpu/instructions/cpu_instruction_op_brk.cpp
    cpu/instructions/cpu_instruction_op_bvc.hpp
    cpu/instructions/cpu_instruction_op_bvc.cpp
    cpu/instructions/cpu_instruction_op_bvs.hpp
    cpu/instructions/cpu_instruction_op_bvs.cpp
    cpu/instructions/cpu_instruction_op_clc.hpp
    cpu/instructions/cpu_instruction_op_clc.cpp
    cpu/instructions/cpu_instruction_op_cld.hpp
    cpu/instructions/cpu_instruction_op_cld.cpp
    cpu/instructions/cpu_instruction_op_cli.hpp
    cpu/instructions/cpu_instruction_op_cli.cpp
    cpu/instructions/cpu_instruction_op_clv.hpp
    cpu/instructions/cpu_instruction_op_clv.cpp
    cpu/instructions/cpu_instruction_op_cmp.hpp
    cpu/instructions/cpu_instruction_op_cmp.cpp
    cpu/instructions/cpu_instruction_op_cpx.hpp
    cpu/instructions/cpu_instruction_op_cpx.cpp
    cpu/instructions/cpu_instruction_op_cpy.hpp
    cpu/instructions/cpu_instruction_op_cpy.cpp
    cpu/instructions/cpu_instruction_op_dec.hpp
    cpu/instructions/cpu_instruction_op_dec.cpp
    cpu/instructions/cpu_instruction_op_dex.hpp
    cpu/instructions/cpu_instruction_op_dex.cpp
    cpu/instructions/cpu_instruction_op_dey.hpp
    cpu/instructions/cpu_instruction_op_dey.cpp
    cpu/instructions/cpu_instruction_op_eor.hpp
    cpu/instructions/cpu_instruction_op_eor.cpp
    cpu/instructions/cpu_instruction_op_inc.hpp
    cpu/instructions/cpu_instruction_op_inc.cpp
    cpu/instructions/cpu_instruction_op_inx.hpp
    cpu/instructions/cpu_instruction_op_inx.cpp
    cpu/instructions/cpu_instruction_op_iny.hpp
    cpu/instructions/cpu_instruction_op_iny.cpp
    cpu/instructions/cpu_instruction_op_jmp.hpp
    cpu/instructions/cpu_instruction_op_jmp.cpp
    cpu/instructions/cpu_instruction_op_jsr.hpp
    cpu/instructions/cpu_instruction_op_jsr.cpp
    cpu/instructions/cpu_instruction_op_lda.hpp
    cpu/instructions/cpu_instruction_op_lda.cpp
    cpu/instructions/cpu_instruction_op_ldx.hpp
    cpu/instructions/cpu_instruction_op_ldx.cpp
    cpu/instructions/cpu_instruction_op_ldy.hpp
    cpu/instructions/cpu_instruction_op_ldy.cpp
    cpu/instructions/cpu_instruction_op_lsr.hpp
    cpu/instructions/cpu_instruction_op_lsr.cpp
    cpu/instructions/cpu_instruction_op_nop.hpp
    cpu/instructions/cpu_instruction_op_nop.cpp
    cpu/instructions/cpu_instruction_op_ora.hpp
    cpu/instructions/cpu_instruction_op_ora.cpp
    cpu/instructions/cpu_instruction_op_pha.hpp
    cpu/instructions/cpu_instruction_op_pha.cpp
    cpu/instructions/cpu_instruction_op_php.hpp
    cpu/instructions/cpu_instruction_op_php.cpp
    cpu/instructions/cpu_instruction_op_pla.hpp
    cpu/instructions/cpu_instruction_op_pla.cpp
    cpu/instructions/cpu_instruction_op_plp.hpp
    cpu/instructions/cpu_instruction_op_plp.cpp
    cpu/instructions/cpu_instruction_op_rol.hpp
    cpu/instructions/cpu_instruction_op_rol.cpp
    cpu/instructions/cpu_instruction_op_ror.hpp
    cpu/instructions/cpu_instruction_op_ror.cpp
    cpu/instructions/cpu_instruction_op_rti.hpp
    cpu/instructions/cpu_instruction_op_rti.cpp
    cpu/instructions/cpu_instruction_op_rts.hpp
    cpu/instructions/cpu_instruction_op_rts.cpp
    cpu/instructions/cpu_instruction_op_sbc.hpp
    cpu/instructions/cpu_instruction_op_sbc.cpp
    cpu/instructions/cpu_instruction_op_sec.hpp
    cpu/instructions/cpu_instruction_op_sec.cpp
    cpu/instructions/cpu_instruction_op_sed.hpp
    cpu/instructions/cpu_instruction_op_sed.cpp
    cpu/instructions/cpu_instruction_op_sei.hpp
    cpu/instructions/cpu_instruction_op_sei.cpp
    cpu/instructions/cpu_instruction_op_sta.hpp
    cpu/instructions/cpu_instruction_op_sta.cpp
    cpu/instructions/cpu_instruction_op_stx.hpp
    cpu/instructions/cpu_instruction_op_stx.cpp
    cpu/instructions/cpu_instruction_op_sty.hpp
    cpu/instructions/cpu_instruction_op_sty.cpp
    cpu/instructions/cpu_instruction_op_tax.hpp
    cpu/instructions/cpu_instruction_op_tax.cpp
    cpu/instructions/cpu_instruction_op_tay.hpp
    cpu/instructions/cpu_instruction_op_tay.cpp
    cpu/instructions/cpu_instruction_op_tsx.hpp
    cpu/instructions/cpu_instruction_op_tsx.cpp
    cpu/instructions/cpu_instruction_op_txa.hpp
    cpu/instructions/cpu_instruction_op_txa.cpp
    cpu/instructions/cpu_instruction_op_txs.hpp
    cpu/instructions/cpu_instruction_op_txs.cpp
    cpu/instructions/cpu_instruction_op_tya.hpp
    cpu/instructions/cpu_instruction_op_tya.cpp
    cpu/flags/cpu_status_flags.hpp
    cpu/flags/cpu_b_flags.hpp
    ram/ram.hpp
    ram/ram.cpp
    editor/editor.hpp
    editor/editor.cpp
    editor/ui/ui_cpu_controller.hpp
    editor/ui/ui_cpu_controller.cpp
    editor/ui/ui_ram_visualizer.hpp
    editor/ui/ui_ram_visualizer.cpp
    editor/ui/ui_rom_browser.hpp
    editor/ui/ui_rom_browser.cpp
    utility/literals.hpp)

# Easiest way to add ImGui to a project is to simply compile the files with the project itself
set(IMGUI_FILES
    _deps/imgui/imgui.cpp
    _deps/imgui/imgui_draw.cpp
    _deps/imgui/imgui_widgets.cpp
    _deps/imgui-sfml/imgui-SFML.cpp)

add_executable(NES ${SOURCE_LIST} ${IMGUI_FILES})

# Configure SFML
set(BUILD_SHARED_LIBS FALSE)
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_SYSTEM FALSE)
add_subdirectory(_deps/SFML)
target_link_libraries(NES PRIVATE sfml-graphics sfml-window)
target_include_directories(NES PRIVATE _deps/SFML/include)

# Include directories for the NES project
target_include_directories(NES PRIVATE ./ _deps/imgui _deps/imgui-sfml)

# Directory structure in IDEs that support it
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST} ${IMGUI_FILES})

# Use C++17
target_compile_features(NES PRIVATE cxx_std_17)
