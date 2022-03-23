% Author(s): Edward Patch
bLinux = false;
dir = "coms/";
name = "coms";
deflib = definecoms;

if ~bLinux
    clibgen.generateLibraryDefinition(fullfile(dir, name + ".h"), ...
        "AdditionalCompilerFlags", '/std:c++17',...
        "SupportingSourceFiles",fullfile(dir, name + ".cpp"), ...
        "OverwriteExistingDefinitionFiles",true, ...
        "ReturnCArrays",false)

else
    clibgen.generateLibraryDefinition(fullfile(dir, name + ".h"), ...
        "SupportingSourceFiles",fullfile(dir, name + ".cpp"), ...
        "OverwriteExistingDefinitionFiles",true, ...
        "ReturnCArrays",false)
end

 build(deflib)
 addpath(name+"/")