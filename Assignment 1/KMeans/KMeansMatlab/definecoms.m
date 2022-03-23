%% About definecoms.mlx
% This file defines the MATLAB interface to the library |coms|.
%
% Commented sections represent C++ functionality that MATLAB cannot automatically define. To include
% functionality, uncomment a section and provide values for &lt;SHAPE&gt;, &lt;DIRECTION&gt;, etc. For more
% information, see <matlab:helpview(fullfile(docroot,'matlab','helptargets.map'),'cpp_define_interface') Define MATLAB Interface for C++ Library>.



%% Setup
% Do not edit this setup section.
function libDef = definecoms()
libDef = clibgen.LibraryDefinition("comsData.xml");
%% OutputFolder and Libraries 
libDef.OutputFolder = "D:\Users\Edward Patch\OneDrive - University of Wales Trinity Saint David\BSC\Year 3\AI-and-ML\Assignment 1\KMeans\KMeansMatlab";
libDef.Libraries = "";

%% C++ class |CMemory| with MATLAB name |clib.coms.CMemory| 
CMemoryDefinition = addClass(libDef, "CMemory", "MATLABName", "clib.coms.CMemory", ...
    "Description", "clib.coms.CMemory    Representation of C++ class CMemory."); % Modify help description values as needed.

%% C++ class constructor for C++ class |CMemory| 
% C++ Signature: CMemory::CMemory(CMemory const & input1)
CMemoryConstructor1Definition = addConstructor(CMemoryDefinition, ...
    "CMemory::CMemory(CMemory const & input1)", ...
    "Description", "clib.coms.CMemory Constructor of C++ class CMemory."); % Modify help description values as needed.
defineArgument(CMemoryConstructor1Definition, "input1", "clib.coms.CMemory", "input");
validate(CMemoryConstructor1Definition);

%% C++ class constructor for C++ class |CMemory| 
% C++ Signature: CMemory::CMemory()
CMemoryConstructor2Definition = addConstructor(CMemoryDefinition, ...
    "CMemory::CMemory()", ...
    "Description", "clib.coms.CMemory Constructor of C++ class CMemory."); % Modify help description values as needed.
validate(CMemoryConstructor2Definition);

%% C++ class public data member |value| for C++ class |CMemory| 
% C++ Signature: int CMemory::value
addProperty(CMemoryDefinition, "value", "int32", ...
    "Description", "int32    Data member of C++ class CMemory."); % Modify help description values as needed.

%% C++ function |CreateCMemory| with MATLAB name |clib.coms.CreateCMemory|
% C++ Signature: int CreateCMemory(char [] name,int size)
%CreateCMemoryDefinition = addFunction(libDef, ...
%    "int CreateCMemory(char [] name,int size)", ...
%    "MATLABName", "clib.coms.CreateCMemory", ...
%    "Description", "clib.coms.CreateCMemory Representation of C++ function CreateCMemory."); % Modify help description values as needed.
%defineArgument(CreateCMemoryDefinition, "name", "clib.array.coms.Char", "input", <SHAPE>); % <MLTYPE> can be "clib.array.coms.Char","int8","string", or "char"
%defineArgument(CreateCMemoryDefinition, "size", "int32");
%defineOutput(CreateCMemoryDefinition, "RetVal", "int32");
%validate(CreateCMemoryDefinition);

%% Validate the library definition
validate(libDef);

end
