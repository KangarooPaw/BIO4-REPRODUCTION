xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 202;
 9.22447;0.49431;-9.22447;,
 9.22447;0.49431;9.22447;,
 0.00000;0.49431;-9.22447;,
 0.00000;0.49431;9.22447;,
 -9.22447;0.49431;9.22447;,
 -9.22447;0.49431;-9.22447;,
 8.72451;4.66176;7.05033;,
 8.72451;9.88328;1.37037;,
 8.72451;11.12218;7.05033;,
 -9.22447;0.49431;-9.22447;,
 -9.22447;0.49431;9.22447;,
 -9.22447;2.85938;7.05033;,
 -9.22447;2.85938;-7.05033;,
 -9.22447;7.13152;9.22447;,
 -9.22447;7.37544;7.05033;,
 -9.22447;8.95740;-7.05033;,
 -9.22447;9.20132;-9.22447;,
 9.22447;0.49431;9.22447;,
 9.22447;0.49431;-9.22447;,
 9.22447;2.85938;-7.05033;,
 9.22447;2.85938;7.05033;,
 9.22447;7.45475;-9.22447;,
 9.22447;7.92896;-7.05033;,
 9.22447;11.00454;7.05033;,
 9.22447;11.47876;9.22447;,
 -8.72451;2.85938;7.05033;,
 -8.72450;2.85938;5.42114;,
 -8.72451;2.85938;-7.05033;,
 -8.72451;4.66176;7.05033;,
 -8.72451;7.52683;7.05033;,
 -8.72451;9.10879;-7.05033;,
 8.72451;2.85938;-7.05033;,
 8.72450;2.85938;5.42114;,
 8.72451;2.85938;7.05033;,
 8.72451;8.05937;-7.05033;,
 0.00000;0.49431;-9.22447;,
 7.13231;2.87159;-9.22447;,
 -7.13231;2.87159;-9.22447;,
 -7.13231;9.83483;-9.22447;,
 7.13231;7.94699;-9.22447;,
 7.13231;2.87159;9.22447;,
 -7.13231;2.87159;9.22447;,
 7.13231;2.87159;-8.70177;,
 4.85489;2.87159;-8.70177;,
 -7.13231;2.87159;-8.70177;,
 -7.13231;9.77619;-8.70177;,
 7.13231;4.27247;-8.70177;,
 7.13231;8.06100;-8.70177;,
 7.13231;2.87159;8.70177;,
 4.85489;2.87159;8.70177;,
 -7.13231;2.87159;8.70177;,
 -1.57790;8.90697;8.70177;,
 -7.13231;7.82368;8.70177;,
 7.13231;2.87159;8.98923;,
 7.13231;4.27247;8.98923;,
 4.85489;2.87159;8.98923;,
 0.85821;10.21098;8.98923;,
 -2.03279;9.33558;8.98923;,
 7.13231;2.87159;-8.98923;,
 7.13231;4.27247;-8.98923;,
 4.85489;2.87159;-8.98923;,
 -3.28675;10.51239;-8.70177;,
 -3.19759;10.42872;-8.98923;,
 7.13231;4.27247;8.70177;,
 0.83240;10.23541;8.70177;,
 8.72451;8.63529;-0.81117;,
 8.94855;9.23886;-1.34246;,
 8.94855;9.84068;1.41672;,
 8.94855;2.85938;5.42114;,
 8.94855;4.66176;7.05033;,
 8.94855;2.85938;7.05033;,
 -8.72451;8.36441;-0.41536;,
 -8.94855;2.85938;7.05033;,
 -8.94855;2.85938;5.42114;,
 -8.94855;4.66176;7.05033;,
 -8.72451;7.92509;3.50049;,
 -8.94855;7.84782;3.58455;,
 7.13231;12.14305;8.70177;,
 4.92374;10.64802;8.70177;,
 7.13231;10.49065;8.70177;,
 -8.94855;8.28741;-0.33372;,
 -7.13231;7.76504;9.22447;,
 -9.22447;7.13152;9.22447;,
 9.22447;12.71792;9.22447;,
 7.13231;12.08441;9.22447;,
 7.13231;11.97100;9.22447;,
 9.22447;11.47876;9.22447;,
 -4.08262;10.69965;-8.70177;,
 9.22447;12.39669;7.05033;,
 9.22447;12.71792;9.22447;,
 8.72451;12.32651;7.05033;,
 1.89375;9.23083;-8.98923;,
 1.80560;9.31427;-8.70177;,
 9.91152;0.03909;-9.91152;,
 9.91152;0.03909;9.91152;,
 0.00000;0.03909;-9.91152;,
 0.00000;0.03909;9.91152;,
 -9.91152;0.03909;9.91152;,
 -9.91152;0.03909;-9.91152;,
 9.37432;4.51694;7.57546;,
 9.37432;10.12737;1.47244;,
 9.37432;11.45854;7.57546;,
 -9.91152;0.03909;-9.91152;,
 -9.91152;0.03909;9.91152;,
 -9.91152;2.58032;7.57546;,
 -9.91152;2.58032;-7.57546;,
 -9.91152;7.17066;9.91152;,
 -9.91152;7.43274;7.57546;,
 -9.91152;9.13253;-7.57546;,
 -9.91152;9.39462;-9.91152;,
 9.91152;0.03909;9.91152;,
 9.91152;0.03909;-9.91152;,
 9.91152;2.58032;-7.57546;,
 9.91152;2.58032;7.57546;,
 9.91152;7.51796;-9.91152;,
 9.91152;8.02749;-7.57546;,
 9.91152;11.33215;7.57546;,
 9.91152;11.84168;9.91152;,
 -9.37432;2.58032;5.82492;,
 -9.37432;2.58032;-7.57546;,
 -9.37432;2.58032;7.57546;,
 -9.37432;4.51694;7.57546;,
 -9.37432;7.59541;7.57546;,
 -9.37432;9.29520;-7.57546;,
 9.37432;2.58032;7.57546;,
 9.37432;2.58032;-7.57546;,
 9.37432;2.58032;5.82492;,
 9.37432;8.16761;-7.57546;,
 0.00000;0.03909;-9.91152;,
 7.66354;2.59344;-9.91152;,
 -7.66354;2.59344;-9.91152;,
 -7.66354;10.07531;-9.91152;,
 7.66354;8.04686;-9.91152;,
 7.66354;2.59344;9.91152;,
 -7.66354;2.59344;9.91152;,
 7.66354;2.59344;-9.34989;,
 5.21649;2.59344;-9.34989;,
 -7.66354;2.59344;-9.34989;,
 -7.66354;10.01230;-9.34989;,
 7.66354;4.09866;-9.34989;,
 7.66354;8.16936;-9.34989;,
 7.66354;2.59344;9.34989;,
 5.21649;2.59344;9.34989;,
 -7.66354;2.59344;9.34989;,
 -1.69542;9.07834;9.34989;,
 -7.66354;7.91436;9.34989;,
 7.66354;2.59344;9.65877;,
 7.66354;4.09866;9.65877;,
 5.21649;2.59344;9.65877;,
 0.92213;10.47948;9.65877;,
 -2.18420;9.53887;9.65877;,
 7.66354;2.59344;-9.65877;,
 7.66354;4.09866;-9.65877;,
 5.21649;2.59344;-9.65877;,
 -3.53155;10.80334;-9.34989;,
 -3.43575;10.71343;-9.65877;,
 7.66354;4.09866;9.34989;,
 0.89439;10.50573;9.34989;,
 9.37432;8.78643;-0.87159;,
 9.61506;9.43495;-1.44245;,
 9.61506;10.08160;1.52224;,
 9.61506;2.58032;5.82492;,
 9.61506;4.51694;7.57546;,
 9.61506;2.58032;7.57546;,
 -9.37432;8.49537;-0.44629;,
 -9.61506;2.58032;7.57546;,
 -9.61506;2.58032;5.82492;,
 -9.61506;4.51694;7.57546;,
 -9.37432;8.02333;3.76122;,
 -9.61506;7.94030;3.85154;,
 7.66354;12.55545;9.34989;,
 5.29047;10.94907;9.34989;,
 7.66354;10.77998;9.34989;,
 -9.61506;8.41263;-0.35857;,
 -7.66354;7.85136;9.91152;,
 -9.91152;7.17066;9.91152;,
 9.91152;13.17314;9.91152;,
 7.66354;12.49244;9.91152;,
 7.66354;12.37059;9.91152;,
 9.91152;11.84168;9.91152;,
 -4.38670;11.00454;-9.34989;,
 9.91152;12.82798;7.57546;,
 9.91152;13.17314;9.91152;,
 9.37432;12.75257;7.57546;,
 2.03480;9.42632;-9.65876;,
 1.94008;9.51598;-9.34989;,
 -9.91000;9.39000;-9.91000;,
 -9.22000;9.20000;-9.22000;,
 -9.37000;9.30000;-7.58000;,
 -9.22000;9.20000;-9.22000;,
 -9.22000;7.13000;9.22000;,
 -9.22000;7.13000;9.22000;,
 -9.22000;7.13000;9.22000;,
 7.13000;12.14000;8.70000;,
 0.86000;10.21000;8.99000;,
 9.22000;12.72000;9.22000;,
 8.72000;11.12000;7.05000;,
 8.72000;9.88000;1.37000;,
 9.37000;8.17000;-7.58000;,
 -3.20000;10.43000;-8.99000;,
 -7.13000;9.78000;-8.70000;,
 -4.08000;10.70000;-8.70000;;
 
 311;
 3;0,1,2;,
 3;1,3,2;,
 3;3,4,2;,
 3;4,5,2;,
 3;6,7,8;,
 4;9,10,11,12;,
 4;11,10,13,14;,
 4;12,15,16,9;,
 4;17,18,19,20;,
 4;19,18,21,22;,
 4;20,23,24,17;,
 3;25,26,11;,
 3;26,27,11;,
 3;27,12,11;,
 3;25,11,28;,
 3;29,28,14;,
 3;28,11,14;,
 4;27,30,15,12;,
 3;19,31,20;,
 3;31,32,20;,
 3;32,33,20;,
 4;31,19,22,34;,
 3;23,20,8;,
 3;20,33,6;,
 3;6,8,20;,
 3;18,35,36;,
 3;36,35,37;,
 3;35,9,37;,
 4;37,9,16,38;,
 4;36,39,21,18;,
 3;1,40,3;,
 3;40,41,3;,
 3;41,4,3;,
 3;42,36,43;,
 3;36,37,43;,
 3;37,44,43;,
 4;44,37,38,45;,
 3;42,46,36;,
 3;46,47,36;,
 3;47,39,36;,
 3;48,49,40;,
 3;40,49,41;,
 3;49,50,41;,
 4;49,51,52,50;,
 3;53,54,55;,
 3;54,56,55;,
 3;56,57,55;,
 4;46,42,58,59;,
 4;42,43,60,58;,
 4;43,61,62,60;,
 4;48,63,54,53;,
 4;63,64,56,54;,
 4;49,48,53,55;,
 4;31,34,65,32;,
 3;66,67,68;,
 3;67,69,68;,
 3;69,70,68;,
 4;27,26,71,30;,
 4;26,25,72,73;,
 4;25,28,74,72;,
 4;28,75,76,74;,
 4;32,65,66,68;,
 4;6,33,70,69;,
 4;33,32,68,70;,
 3;77,78,79;,
 3;72,74,73;,
 3;74,76,73;,
 3;76,80,73;,
 4;81,82,4,41;,
 4;83,84,85,86;,
 4;52,81,41,50;,
 4;84,77,79,85;,
 3;43,44,61;,
 3;61,44,87;,
 3;44,45,87;,
 4;57,51,49,55;,
 3;29,75,28;,
 4;80,71,26,73;,
 4;24,23,88,89;,
 4;23,8,90,88;,
 3;58,60,59;,
 3;59,60,91;,
 3;60,62,91;,
 4;79,78,64,63;,
 4;86,85,40,1;,
 3;85,79,40;,
 3;40,79,63;,
 3;63,48,40;,
 4;91,92,46,59;,
 4;67,7,6,69;,
 3;93,94,95;,
 3;94,96,95;,
 3;96,97,95;,
 3;97,98,95;,
 3;99,100,101;,
 4;102,103,104,105;,
 4;104,103,106,107;,
 4;105,108,109,102;,
 4;110,111,112,113;,
 4;112,111,114,115;,
 4;113,116,117,110;,
 3;118,119,120;,
 3;119,105,120;,
 3;105,104,120;,
 3;120,104,121;,
 3;122,121,107;,
 3;121,104,107;,
 4;119,123,108,105;,
 3;113,112,124;,
 3;112,125,124;,
 3;125,126,124;,
 4;125,112,115,127;,
 3;116,113,101;,
 3;113,124,101;,
 3;124,99,101;,
 3;111,128,129;,
 3;129,128,130;,
 3;128,102,130;,
 4;130,102,109,131;,
 4;129,132,114,111;,
 3;94,133,96;,
 3;133,134,96;,
 3;134,97,96;,
 3;135,129,136;,
 3;129,130,136;,
 3;130,137,136;,
 4;137,130,131,138;,
 3;135,139,129;,
 3;139,140,129;,
 3;140,132,129;,
 3;141,142,133;,
 3;133,142,134;,
 3;142,143,134;,
 4;142,144,145,143;,
 3;146,147,148;,
 3;147,149,148;,
 3;149,150,148;,
 4;139,135,151,152;,
 4;135,136,153,151;,
 4;136,154,155,153;,
 4;141,156,147,146;,
 4;156,157,149,147;,
 4;142,141,146,148;,
 4;125,127,158,126;,
 3;159,160,161;,
 3;160,162,161;,
 3;162,163,161;,
 4;119,118,164,123;,
 4;118,120,165,166;,
 4;120,121,167,165;,
 4;121,168,169,167;,
 4;126,158,159,161;,
 4;99,124,163,162;,
 4;124,126,161,163;,
 3;170,171,172;,
 3;165,167,166;,
 3;167,169,166;,
 3;169,173,166;,
 4;174,175,97,134;,
 4;176,177,178,179;,
 4;145,174,134,143;,
 4;177,170,172,178;,
 3;136,137,154;,
 3;154,137,180;,
 3;137,138,180;,
 4;150,144,142,148;,
 3;122,168,121;,
 4;173,164,118,166;,
 4;117,116,181,182;,
 4;116,101,183,181;,
 3;151,153,152;,
 3;152,153,184;,
 3;153,155,184;,
 4;172,171,157,156;,
 4;179,178,133,94;,
 3;178,172,133;,
 3;133,172,156;,
 3;156,141,133;,
 4;184,185,139,152;,
 4;160,100,99,162;,
 3;109,138,131;,
 3;108,16,109;,
 4;186,109,16,138;,
 4;38,138,16,187;,
 3;2,1,0;,
 3;2,3,1;,
 3;2,4,3;,
 3;2,5,4;,
 3;8,7,6;,
 4;12,11,10,9;,
 4;14,13,10,11;,
 4;9,16,15,12;,
 4;20,19,18,17;,
 4;22,21,18,19;,
 4;17,24,23,20;,
 3;11,26,25;,
 3;11,27,26;,
 3;11,12,27;,
 3;28,11,25;,
 3;14,28,29;,
 3;14,11,28;,
 4;12,15,30,27;,
 3;20,31,19;,
 3;20,32,31;,
 3;20,33,32;,
 4;34,22,19,31;,
 3;8,20,23;,
 3;6,33,20;,
 3;20,8,6;,
 3;36,35,18;,
 3;37,35,36;,
 3;37,9,35;,
 4;38,16,9,37;,
 4;18,21,39,36;,
 3;3,40,1;,
 3;3,41,40;,
 3;3,4,41;,
 3;43,36,42;,
 3;43,37,36;,
 3;43,44,37;,
 4;45,38,37,44;,
 3;36,46,42;,
 3;36,47,46;,
 3;36,39,47;,
 3;40,49,48;,
 3;41,49,40;,
 3;41,50,49;,
 4;50,52,51,49;,
 3;55,54,53;,
 3;55,56,54;,
 3;55,57,56;,
 4;59,58,42,46;,
 4;58,60,43,42;,
 4;60,62,61,43;,
 4;53,54,63,48;,
 4;54,56,64,63;,
 4;55,53,48,49;,
 4;32,65,34,31;,
 3;68,67,66;,
 3;68,69,67;,
 3;68,70,69;,
 4;30,71,26,27;,
 4;73,72,25,26;,
 4;72,74,28,25;,
 4;74,76,75,28;,
 4;68,66,65,32;,
 4;69,70,33,6;,
 4;70,68,32,33;,
 3;79,78,77;,
 3;73,74,72;,
 3;73,76,74;,
 3;73,80,76;,
 4;41,4,82,81;,
 4;86,85,84,83;,
 4;50,41,81,52;,
 4;85,79,77,84;,
 3;61,44,43;,
 3;87,44,61;,
 3;87,45,44;,
 4;55,49,51,57;,
 3;28,75,29;,
 4;73,26,71,80;,
 4;89,88,23,24;,
 4;88,90,8,23;,
 3;59,60,58;,
 3;91,60,59;,
 3;91,62,60;,
 4;63,64,78,79;,
 4;1,40,85,86;,
 3;40,79,85;,
 3;63,79,40;,
 3;40,48,63;,
 4;59,46,92,91;,
 4;69,6,7,67;,
 4;188,123,187,108;,
 4;123,15,187,189;,
 4;123,164,80,15;,
 4;71,30,15,80;,
 4;173,169,168,164;,
 4;168,76,80,164;,
 4;29,75,76,14;,
 4;122,14,76,168;,
 4;107,175,82,122;,
 4;190,13,14,122;,
 3;175,174,145;,
 4;191,190,145,81;,
 4;175,145,190,192;,
 4;51,52,81,57;,
 4;144,57,81,145;,
 4;56,57,144,150;,
 4;157,56,150,149;,
 4;157,84,77,193;,
 4;77,78,64,56;,
 4;194,157,77,56;,
 4;170,177,176,89;,
 4;89,176,181,183;,
 4;183,88,89,195;,
 4;23,100,67,8;,
 4;196,67,7,197;,
 4;159,158,100,160;,
 4;100,158,66,67;,
 4;127,22,66,158;,
 4;34,65,66,22;,
 4;115,114,127,198;,
 4;127,114,21,22;,
 4;140,21,114,132;,
 4;91,184,155,62;,
 4;199,61,62,154;,
 4;87,38,45,200;,
 4;201,87,61,38;,
 4;61,62,154,180;;
 
 MeshMaterialList {
  2;
  311;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.216000;0.136000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.216000;0.136000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  193;
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000001;,
  -0.000001;1.000000;-0.000000;,
  0.000001;1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  -0.981151;-0.193245;0.000000;,
  0.981151;0.193245;-0.000001;,
  0.143211;0.989692;-0.000000;,
  0.143199;0.989694;-0.000449;,
  0.918536;0.395337;-0.000001;,
  -0.367982;-0.929833;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;-0.155500;-0.987836;,
  -0.042238;0.983107;0.178089;,
  -0.000000;0.983476;0.181038;,
  -0.000001;-0.929371;-0.369146;,
  0.000000;-1.000000;-0.000001;,
  0.000001;0.402012;0.915635;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  0.687417;0.726263;-0.000003;,
  -0.153027;0.896344;0.416112;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.229887;0.932003;0.280218;,
  -0.684323;-0.729179;0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.687417;0.726263;-0.000001;,
  0.000000;0.000000;-1.000000;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000000;-0.000001;,
  0.000000;1.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  0.918536;0.395337;-0.000000;,
  0.918536;0.395337;-0.000000;,
  -0.367982;-0.929833;0.000001;,
  -0.000000;-0.929371;-0.369146;,
  -0.000000;0.402012;0.915635;,
  1.000000;-0.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.687417;0.726263;-0.000001;,
  0.229885;0.932004;0.280218;,
  -1.000000;-0.000000;0.000000;,
  -0.153031;0.896344;0.416112;,
  -1.000000;-0.000000;-0.000001;,
  -0.684323;-0.729179;0.000001;,
  1.000000;-0.000000;-0.000000;,
  0.687417;0.726263;-0.000001;,
  0.000000;0.000000;-1.000000;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.422792;0.888525;-0.178242;,
  -0.234477;0.574666;0.784079;,
  -0.079043;0.261039;-0.962087;,
  0.878264;0.475012;0.054920;,
  0.732984;-0.675764;-0.077954;,
  -0.111995;0.374657;-0.920374;,
  -0.378363;0.821465;-0.426658;,
  -0.562420;0.821982;0.089604;,
  -0.279660;0.937983;0.204887;,
  -0.966075;-0.255724;0.036118;,
  -0.189463;0.959376;-0.209050;,
  0.006850;0.026260;-0.999632;,
  0.384518;0.883092;0.268875;,
  -0.619962;0.780092;0.084285;,
  -0.162872;0.863191;-0.477885;,
  -0.000001;1.000000;0.000000;,
  0.000001;1.000000;0.000000;,
  0.000000;-0.196331;-0.980538;,
  0.981151;0.193245;-0.000000;,
  -0.143211;-0.989692;0.000000;,
  0.918536;0.395337;-0.000001;,
  -0.143199;-0.989694;0.000449;,
  -0.367949;-0.929845;0.001153;,
  0.000000;-0.983476;-0.181038;,
  0.000000;0.155500;0.987836;,
  0.042238;-0.983107;-0.178089;,
  0.159875;-0.721146;-0.674083;,
  0.086170;-0.927671;-0.363320;,
  -0.000000;0.196331;0.980538;,
  -0.000001;0.402012;0.915634;,
  -0.883861;0.464995;0.050689;,
  -0.718256;0.686238;0.114827;,
  -0.684271;-0.729225;0.002144;,
  -0.000001;-0.727463;-0.686147;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000001;-1.000000;,
  -0.981151;-0.193245;0.000001;,
  0.474183;0.864760;0.165351;,
  -0.038841;0.998856;-0.027892;,
  -0.107098;0.958451;0.264389;,
  0.000000;0.000000;0.000000;,
  0.003425;0.013131;-0.999908;,
  -1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;-0.000002;,
  -0.367949;-0.929846;0.001153;,
  0.086170;-0.927671;-0.363320;,
  0.159875;-0.721146;-0.674083;,
  0.000000;0.402012;0.915634;,
  -0.684271;-0.729225;0.002144;,
  -0.000000;-0.727462;-0.686147;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.474183;0.864760;0.165351;,
  0.000001;0.736192;0.676773;,
  -0.133079;0.990407;-0.037188;,
  0.105913;0.994283;0.013564;,
  -0.039622;0.958358;0.282809;,
  -0.288152;0.951614;0.106765;,
  0.165768;0.980016;0.109949;,
  0.300250;0.953224;-0.034839;,
  -0.124130;0.304224;0.944478;,
  0.919048;0.389604;0.059658;,
  0.930856;-0.362980;-0.041872;,
  0.904889;0.423493;0.042774;,
  -0.925217;0.359776;-0.120560;,
  0.000001;-1.000000;-0.000000;,
  0.000001;-1.000000;0.000000;,
  -0.000001;-1.000000;-0.000000;,
  -0.000001;-1.000000;0.000000;,
  -0.899989;0.433390;0.046825;,
  -0.046429;0.282443;-0.958160;,
  -0.918536;-0.395337;0.000001;,
  0.367982;0.929833;-0.000000;,
  0.458030;0.866496;0.198479;,
  0.390133;0.920743;-0.005283;,
  -0.918536;-0.395337;0.000001;,
  -0.687417;-0.726263;0.000003;,
  0.367949;0.929845;-0.001153;,
  -1.000000;0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000001;,
  1.000000;0.000000;-0.000000;,
  0.000001;0.929371;0.369146;,
  -0.000001;-0.402012;-0.915635;,
  -0.000001;-0.736192;-0.676773;,
  -0.086170;0.927671;0.363320;,
  -0.271838;0.952035;0.140473;,
  -0.355906;0.889027;0.288032;,
  0.000001;-0.402012;-0.915634;,
  -0.070540;0.429119;-0.900489;,
  0.788618;0.611651;0.062970;,
  -0.166493;0.642132;-0.748296;,
  0.684271;0.729225;-0.002144;,
  0.014089;0.989791;-0.141826;,
  -0.153346;0.893551;0.421961;,
  -0.991482;-0.128961;0.018214;,
  0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;-0.000001;1.000000;,
  -0.687417;-0.726263;0.000001;,
  0.000002;-0.736192;-0.676773;,
  0.791884;0.607580;0.061367;,
  0.557733;0.825656;0.085002;,
  -0.288154;0.951614;0.106762;,
  -0.288155;0.951614;0.106762;,
  -0.288150;0.951615;0.106762;,
  0.344277;0.923304;0.170245;,
  -0.057767;0.977549;0.202635;,
  -0.254420;0.966216;-0.041191;,
  -0.288153;0.951614;0.106761;,
  -0.306519;0.936514;-0.170259;,
  -0.262646;0.640668;-0.721499;,
  -0.229020;0.859389;-0.457166;,
  -0.325546;0.927384;-0.184330;,
  -0.345628;0.934718;-0.082722;,
  -0.367426;0.902642;-0.224134;,
  -0.396471;0.917958;0.012804;,
  -0.312943;0.914287;-0.257189;,
  -0.189572;0.975628;-0.110509;,
  -0.245939;0.965423;-0.086447;,
  -0.301356;0.951490;-0.062052;,
  -0.162926;0.967857;-0.191595;,
  -0.511868;0.825341;-0.238332;,
  -0.139857;0.954518;-0.263317;,
  0.213756;0.901761;-0.375680;,
  -0.432860;0.881059;-0.190704;,
  -0.293084;0.944208;-0.150240;,
  -0.475187;0.865191;-0.160132;,
  -0.712053;0.665742;-0.223089;,
  0.331965;0.941553;0.057246;,
  0.217329;0.923706;0.315491;,
  0.443812;0.866093;0.230029;,
  -0.420361;0.882398;-0.211353;,
  0.500748;0.844492;0.189960;;
  311;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  3;3,18,70;,
  3;18,4,70;,
  3;4,8,70;,
  3;6,6,16;,
  3;6,16,6;,
  3;16,6,6;,
  4;7,7,7,7;,
  3;8,5,71;,
  3;5,17,71;,
  3;17,3,71;,
  4;7,7,7,7;,
  3;6,6,6;,
  3;6,6,72;,
  3;72,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;8,8,11;,
  3;8,8,11;,
  3;8,8,11;,
  4;2,2,2,2;,
  3;1,9,1;,
  3;9,1,1;,
  3;1,1,1;,
  3;8,12,8;,
  3;8,12,8;,
  3;12,8,8;,
  4;7,7,7,7;,
  3;15,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  4;73,2,2,13;,
  4;0,74,14,0;,
  4;74,29,29,14;,
  4;2,10,75,2;,
  4;10,24,24,75;,
  4;76,0,0,77;,
  4;33,33,33,33;,
  3;34,30,22;,
  3;30,2,22;,
  3;2,23,22;,
  4;26,26,26,26;,
  4;78,20,20,19;,
  4;7,79,21,7;,
  4;79,25,28,21;,
  4;80,81,81,82;,
  4;83,7,7,84;,
  4;20,80,82,20;,
  3;7,7,7;,
  3;27,1,1;,
  3;1,1,1;,
  3;1,27,1;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;85,86,1,1;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;87,87,76,77;,
  3;1,1,1;,
  4;88,88,78,19;,
  4;2,2,2,2;,
  4;6,6,6,6;,
  3;43,89,90;,
  3;90,89,32;,
  3;89,91,32;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  3;1,1,1;,
  3;1,1,92;,
  3;92,1,1;,
  4;93,31,73,13;,
  4;94,95,83,84;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;43,6,6;,
  3;43,6,6;,
  3;6,6,6;,
  4;7,7,7,7;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  4;7,7,7,7;,
  3;6,6,6;,
  3;6,6,6;,
  3;96,96,96;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;6,6,6,6;,
  4;6,6,97,6;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,35,8;,
  4;2,2,2,2;,
  3;1,36,98;,
  3;36,48,98;,
  3;48,99,98;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,35,8;,
  4;7,7,7,7;,
  3;15,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  4;38,2,2,38;,
  4;0,39,39,0;,
  4;39,49,49,39;,
  4;2,37,37,2;,
  4;37,44,44,37;,
  4;100,0,0,100;,
  4;53,53,53,53;,
  3;54,50,42;,
  3;50,2,42;,
  3;2,2,42;,
  4;46,46,46,46;,
  4;40,0,0,40;,
  4;7,41,41,7;,
  4;41,45,47,41;,
  4;101,102,102,101;,
  4;103,7,7,103;,
  4;0,101,101,0;,
  3;7,7,7;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,27,1;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  4;104,104,100,100;,
  3;1,1,1;,
  4;105,105,40,40;,
  4;2,2,2,2;,
  4;6,6,6,6;,
  3;43,106,107;,
  3;107,106,52;,
  3;106,108,52;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;109,51,38,38;,
  4;110,111,103,103;,
  3;112,113,114;,
  3;115,116,112;,
  4;55,112,116,113;,
  4;117,113,117,56;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;1,1,1;,
  4;2,2,2,2;,
  4;118,119,2,2;,
  4;2,2,120,2;,
  4;1,1,1,1;,
  4;121,121,1,1;,
  4;1,1,1,1;,
  3;122,78,20;,
  3;122,123,78;,
  3;122,0,123;,
  3;79,7,7;,
  3;7,79,7;,
  3;7,7,79;,
  4;6,6,6,6;,
  3;124,125,0;,
  3;124,80,125;,
  3;124,20,80;,
  4;6,6,6,6;,
  3;7,7,7;,
  3;83,7,7;,
  3;7,7,83;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  4;117,117,7,7;,
  4;7,7,7,7;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;74,0,0;,
  3;74,0,0;,
  3;74,0,0;,
  4;126,126,1,1;,
  3;2,73,2;,
  3;2,2,73;,
  3;2,2,2;,
  3;0,76,0;,
  3;0,76,0;,
  3;0,0,76;,
  4;6,6,6,6;,
  3;6,6,43;,
  3;6,127,6;,
  3;6,6,127;,
  4;128,1,1,9;,
  4;8,129,11,8;,
  4;129,130,131,11;,
  4;1,132,92,1;,
  4;132,133,133,92;,
  4;134,8,8,12;,
  4;135,135,135,135;,
  3;136,137,138;,
  3;136,1,137;,
  3;136,27,1;,
  4;139,139,139,139;,
  4;140,3,3,18;,
  4;6,141,16,6;,
  4;141,142,142,16;,
  4;143,144,145,17;,
  4;146,6,6,72;,
  4;3,143,17,3;,
  3;6,127,147;,
  3;2,2,23;,
  3;2,2,2;,
  3;2,148,2;,
  4;6,6,6,149;,
  4;6,6,6,6;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  4;134,12,150,151;,
  3;2,2,2;,
  4;140,18,152,152;,
  4;153,153,1,1;,
  4;7,7,7,7;,
  3;154,155,15;,
  3;156,155,154;,
  3;156,157,155;,
  4;6,147,127,6;,
  4;6,6,6,6;,
  3;2,2,2;,
  3;10,2,2;,
  3;2,2,10;,
  4;128,9,158,158;,
  4;146,72,159,159;,
  4;57,57,57,57;,
  4;160,120,58,58;,
  4;160,161,148,120;,
  4;152,162,162,152;,
  4;163,47,45,163;,
  4;45,28,148,161;,
  4;164,25,28,164;,
  4;165,118,28,45;,
  4;166,167,166,165;,
  4;59,119,59,59;,
  3;167,168,169;,
  4;60,170,60,149;,
  4;167,169,170,61;,
  4;171,171,149,171;,
  4;172,151,149,169;,
  4;173,151,172,174;,
  4;175,173,174,176;,
  4;175,85,86,62;,
  4;147,127,147,127;,
  4;63,175,86,173;,
  4;177,177,178,178;,
  4;178,178,179,179;,
  4;64,153,153,64;,
  4;180,111,94,180;,
  4;65,94,95,65;,
  4;181,182,111,181;,
  4;111,182,183,94;,
  4;184,185,144,182;,
  4;186,145,144,185;,
  4;66,97,66,66;,
  4;184,187,121,121;,
  4;188,188,188,188;,
  4;93,109,189,130;,
  4;67,131,130,190;,
  4;191,126,126,68;,
  4;69,191,131,69;,
  4;131,130,190,192;;
 }
 MeshTextureCoords {
  202;
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.125000;0.032845;,
  0.225704;0.127998;,
  0.125000;0.150574;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.089940;,
  0.875000;0.082297;,
  0.625000;0.111125;,
  0.625000;0.117988;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.000000;,
  0.125000;0.000000;,
  0.375000;0.094320;,
  0.375000;0.092384;,
  0.125000;0.148431;,
  0.125000;0.148849;,
  0.875000;0.000000;,
  0.846115;0.000000;,
  0.625000;0.000000;,
  0.875000;0.032845;,
  0.875000;0.085056;,
  0.625000;0.113884;,
  0.375000;0.000000;,
  0.153885;0.000000;,
  0.125000;0.000000;,
  0.375000;0.094528;,
  0.500000;0.000000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.127119;,
  0.375000;0.092655;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.375000;0.000000;,
  0.414914;0.000000;,
  0.625000;0.000000;,
  0.625000;0.126048;,
  0.375000;0.025574;,
  0.375000;0.094736;,
  0.375000;0.750000;,
  0.414914;0.750000;,
  0.625000;0.750000;,
  0.536082;0.631550;,
  0.625000;0.659596;,
  0.375000;0.750000;,
  0.375000;0.724426;,
  0.414914;0.750000;,
  0.484959;0.616014;,
  0.535627;0.631996;,
  0.375000;0.000000;,
  0.375000;0.025574;,
  0.414914;0.000000;,
  0.557603;0.139488;,
  0.556041;0.137960;,
  0.375000;0.724426;,
  0.485412;0.615568;,
  0.274606;0.117035;,
  0.273801;0.116254;,
  0.224882;0.127221;,
  0.153885;0.000000;,
  0.125000;0.032845;,
  0.125000;0.000000;,
  0.742636;0.100319;,
  0.875000;0.000000;,
  0.846115;0.000000;,
  0.875000;0.032845;,
  0.812063;0.092313;,
  0.813553;0.090905;,
  0.375000;0.580743;,
  0.384317;0.583682;,
  0.375000;0.585965;,
  0.744083;0.098916;,
  0.625000;0.660667;,
  0.625000;0.660060;,
  0.375000;0.584359;,
  0.375000;0.581814;,
  0.375000;0.583884;,
  0.375000;0.601151;,
  0.571552;0.142906;,
  0.125000;0.184099;,
  0.125000;0.165641;,
  0.125000;0.181340;,
  0.466810;0.116092;,
  0.468355;0.117615;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.125000;0.032845;,
  0.225704;0.127998;,
  0.125000;0.150574;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.089940;,
  0.875000;0.082297;,
  0.625000;0.111125;,
  0.625000;0.117988;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.000000;,
  0.125000;0.000000;,
  0.375000;0.094320;,
  0.375000;0.092384;,
  0.125000;0.148431;,
  0.125000;0.148849;,
  0.846115;0.000000;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.032845;,
  0.875000;0.085056;,
  0.625000;0.113884;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.153885;0.000000;,
  0.375000;0.094528;,
  0.500000;0.000000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.127119;,
  0.375000;0.092655;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.375000;0.000000;,
  0.414914;0.000000;,
  0.625000;0.000000;,
  0.625000;0.126048;,
  0.375000;0.025574;,
  0.375000;0.094736;,
  0.375000;0.750000;,
  0.414914;0.750000;,
  0.625000;0.750000;,
  0.536082;0.631550;,
  0.625000;0.659596;,
  0.375000;0.750000;,
  0.375000;0.724426;,
  0.414914;0.750000;,
  0.484959;0.616014;,
  0.535627;0.631996;,
  0.375000;0.000000;,
  0.375000;0.025574;,
  0.414914;0.000000;,
  0.557603;0.139488;,
  0.556041;0.137960;,
  0.375000;0.724426;,
  0.485412;0.615568;,
  0.274606;0.117035;,
  0.273801;0.116254;,
  0.224882;0.127221;,
  0.153885;0.000000;,
  0.125000;0.032845;,
  0.125000;0.000000;,
  0.742636;0.100319;,
  0.875000;0.000000;,
  0.846115;0.000000;,
  0.875000;0.032845;,
  0.812063;0.092313;,
  0.813553;0.090905;,
  0.375000;0.580743;,
  0.384317;0.583682;,
  0.375000;0.585965;,
  0.744083;0.098916;,
  0.625000;0.660667;,
  0.625000;0.660060;,
  0.375000;0.584359;,
  0.375000;0.581814;,
  0.375000;0.583884;,
  0.375000;0.601151;,
  0.571552;0.142906;,
  0.125000;0.184099;,
  0.125000;0.165641;,
  0.125000;0.181340;,
  0.466810;0.116092;,
  0.468355;0.117615;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}