rem slangc.exe vert.slang -target spirv -o vert.spv -entry vertexMain
rem slangc.exe frag.slang -target spirv -o frag.spv -entry fragmentMain

slangc.exe vert.slang -target spirv -o vert.spv -entry vertexMain
slangc.exe frag.slang -target spirv -o frag.spv -entry fragmentMain
slangc.exe fragBright.slang -target spirv -o fragBright.spv -entry fragmentMain
slangc.exe fragDoubleTexture.slang -target spirv -o fragDoubleTexture.spv -entry fragmentMain