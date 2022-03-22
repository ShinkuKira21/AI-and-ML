%% About definetestlibrary.mlx
% This file defines the MATLAB interface to the library |testlibrary|.
%
% Commented sections represent C++ functionality that MATLAB cannot automatically define. To include
% functionality, uncomment a section and provide values for &lt;SHAPE&gt;, &lt;DIRECTION&gt;, etc. For more
% information, see <matlab:helpview(fullfile(docroot,'matlab','helptargets.map'),'cpp_define_interface') Define MATLAB Interface for C++ Library>.



%% Setup. Do not edit this section.
function libDef = definetestlibrary()
libDef = clibgen.LibraryDefinition("testlibraryData.xml");
%% OutputFolder and Libraries 
libDef.OutputFolder = "/home/edwardpatch1/University of Wales Trinity St Davids/AI-and-ML/Assignment 1/KMeans/KMeansMatlab";
libDef.Libraries = "";

%% C++ class |A| with MATLAB name |clib.testlibrary.A| 
ADefinition = addClass(libDef, "A", "MATLABName", "clib.testlibrary.A", ...
    "Description", "clib.testlibrary.A    Representation of C++ class A."); % Modify help description values as needed.

%% C++ class constructor for C++ class |A| 
% C++ Signature: A::A(A const & input1)
AConstructor1Definition = addConstructor(ADefinition, ...
    "A::A(A const & input1)", ...
    "Description", "clib.testlibrary.A    Constructor of C++ class A."); % Modify help description values as needed.
defineArgument(AConstructor1Definition, "input1", "clib.testlibrary.A", "input");
validate(AConstructor1Definition);

%% C++ class constructor for C++ class |A| 
% C++ Signature: A::A()
AConstructor2Definition = addConstructor(ADefinition, ...
    "A::A()", ...
    "Description", "clib.testlibrary.A    Constructor of C++ class A."); % Modify help description values as needed.
validate(AConstructor2Definition);

%% C++ class public data member |x| for C++ class |A| 
% C++ Signature: int A::x
addProperty(ADefinition, "x", "int32", ...
    "Description", "int32    Data member of C++ class A."); % Modify help description values as needed.

%% C++ class public data member |y| for C++ class |A| 
% C++ Signature: int A::y
addProperty(ADefinition, "y", "int32", ...
    "Description", "int32    Data member of C++ class A."); % Modify help description values as needed.

%% C++ function |XPlusY| with MATLAB name |clib.testlibrary.XPlusY|
% C++ Signature: float XPlusY(float x,float y)
XPlusYDefinition = addFunction(libDef, ...
    "float XPlusY(float x,float y)", ...
    "MATLABName", "clib.testlibrary.XPlusY", ...
    "Description", "clib.testlibrary.XPlusY    Representation of C++ function XPlusY."); % Modify help description values as needed.
defineArgument(XPlusYDefinition, "x", "single");
defineArgument(XPlusYDefinition, "y", "single");
defineOutput(XPlusYDefinition, "RetVal", "single");
validate(XPlusYDefinition);

%% C++ function |RandomNumber| with MATLAB name |clib.testlibrary.RandomNumber|
% C++ Signature: int RandomNumber()
RandomNumberDefinition = addFunction(libDef, ...
    "int RandomNumber()", ...
    "MATLABName", "clib.testlibrary.RandomNumber", ...
    "Description", "clib.testlibrary.RandomNumber    Representation of C++ function RandomNumber."); % Modify help description values as needed.
defineOutput(RandomNumberDefinition, "RetVal", "int32");
validate(RandomNumberDefinition);

%% C++ function |XY| with MATLAB name |clib.testlibrary.XY|
% C++ Signature: int XY(A xy)
XYDefinition = addFunction(libDef, ...
    "int XY(A xy)", ...
    "MATLABName", "clib.testlibrary.XY", ...
    "Description", "clib.testlibrary.XY    Representation of C++ function XY."); % Modify help description values as needed.
defineArgument(XYDefinition, "xy", "clib.testlibrary.A");
defineOutput(XYDefinition, "RetVal", "int32");
validate(XYDefinition);

%% Validate the library definition
validate(libDef);

end
