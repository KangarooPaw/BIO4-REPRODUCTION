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
 51;
 -0.43122;-0.60034;-0.58046;,
 -1.75737;-1.10247;-0.98970;,
 -1.75737;-0.36521;-1.33335;,
 -0.25634;-0.09612;-0.92465;,
 -2.40218;-1.09909;-1.39220;,
 -3.18417;-0.94359;-1.84221;,
 -3.66776;-0.14647;-1.86103;,
 -2.40218;-0.42162;-1.73584;,
 -2.27573;1.07398;-1.22374;,
 -0.28784;0.43290;-0.81696;,
 -3.71049;-0.00786;-1.12721;,
 -3.52564;1.64386;-0.97092;,
 0.03699;0.72804;0.05718;,
 -2.27573;1.25092;0.05709;,
 -2.27573;1.07398;1.33898;,
 -0.28784;0.43290;0.93220;,
 -3.52564;1.88761;-0.11957;,
 -3.52564;1.61392;1.36397;,
 -1.75737;-0.09612;1.44858;,
 -0.25634;-0.09612;1.03879;,
 -4.38218;0.58594;1.44858;,
 -1.75737;-0.67471;1.10494;,
 -0.43122;-0.60034;0.69570;,
 -2.69903;-0.17367;1.25158;,
 -1.75737;-0.66521;0.05709;,
 -0.60377;-0.57733;0.05718;,
 -3.32905;-0.81558;-0.82114;,
 -4.69371;-0.30449;-0.50307;,
 -3.52045;-1.22062;-0.73497;,
 -3.35624;-1.22880;0.86003;,
 -4.72847;-0.30449;1.26904;,
 -3.52564;1.88761;-0.11957;,
 -4.64324;0.41371;-0.61487;,
 -4.38218;0.58594;1.44858;,
 -3.52564;1.61392;1.36397;,
 -0.43122;-0.60034;0.69570;,
 -0.60377;-0.57733;0.05718;,
 0.57546;-0.09612;0.05718;,
 -0.25634;-0.09612;1.03879;,
 0.03699;0.72804;0.05718;,
 -0.28784;0.43290;0.93220;,
 -3.22690;-0.86478;-1.10839;,
 -3.32905;-0.81558;-0.82114;,
 -3.22690;-0.86478;-1.10839;,
 -1.75737;-1.10247;-0.98970;,
 -0.43122;-0.60034;-0.58046;,
 -3.95173;-0.54870;-1.08047;,
 -4.15869;-0.20877;-1.09929;,
 -4.11596;-0.34738;-1.50179;,
 -3.90900;-0.62751;-1.48297;,
 -2.69903;-0.17367;1.25158;;
 
 36;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,2,8,9;,
 4;2,10,11,8;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;15,14,18,19;,
 4;14,17,20,18;,
 4;19,18,21,22;,
 4;18,20,23,21;,
 4;22,21,24,25;,
 4;21,23,26,24;,
 4;27,28,29,30;,
 4;31,32,33,34;,
 4;35,36,37,38;,
 4;38,37,39,40;,
 4;9,8,13,12;,
 4;8,11,16,13;,
 4;10,32,31,11;,
 4;41,42,32,10;,
 4;24,26,43,44;,
 4;25,24,44,45;,
 4;37,36,0,3;,
 4;39,37,3,9;,
 4;1,41,5,4;,
 4;46,47,48,49;,
 4;10,2,7,6;,
 4;2,1,4,7;,
 4;41,10,47,46;,
 4;10,6,48,47;,
 4;6,5,49,48;,
 4;5,41,46,49;,
 4;32,42,28,27;,
 4;42,50,29,28;,
 4;50,33,30,29;,
 4;33,32,27,30;;
 
 MeshMaterialList {
  23;
  36;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.800000;0.320000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.168000;0.168000;0.024000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.080000;0.104000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.264000;0.296000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.040000;0.024000;0.040000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.016000;0.008000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.128000;0.120000;0.120000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.080000;0.736000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.048000;0.048000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.648000;0.544000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.648000;0.544000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.648000;0.544000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.648000;0.544000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.648000;0.544000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.168000;0.168000;0.024000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.048000;0.080000;0.104000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.648000;0.544000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.648000;0.544000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  59;
  0.478783;-0.698063;-0.532425;,
  0.431938;-0.441681;-0.786351;,
  -0.483687;-0.873530;-0.054710;,
  0.585890;-0.243883;-0.772822;,
  0.263083;-0.167735;-0.950080;,
  -0.600447;-0.002941;-0.799659;,
  0.531418;0.278037;-0.800182;,
  0.056907;0.132273;-0.989578;,
  -0.427397;0.273695;-0.861640;,
  0.566850;0.694641;0.442894;,
  0.342127;0.917722;0.201832;,
  0.412563;0.899351;0.144778;,
  0.484049;-0.001512;0.875039;,
  0.109326;-0.210026;0.971564;,
  -0.025787;-0.249034;0.968151;,
  0.315276;-0.875280;0.366723;,
  -0.033920;-0.859182;0.510545;,
  -0.149590;-0.655406;0.740315;,
  0.632126;0.774865;-0.000064;,
  0.354583;0.934966;-0.010445;,
  0.427219;0.903916;-0.020500;,
  -0.874236;0.452951;-0.174775;,
  -0.436941;-0.899417;-0.011436;,
  -0.046248;-0.985492;0.163301;,
  0.351304;-0.934342;0.059929;,
  0.555489;-0.831524;0.000182;,
  0.386237;-0.291321;-0.875188;,
  -0.129699;-0.306849;-0.942879;,
  -0.631871;-0.770189;0.086880;,
  -0.830175;-0.554404;0.058705;,
  -0.748947;-0.520451;-0.410133;,
  -0.659837;-0.712206;-0.239536;,
  -0.584638;-0.810946;0.023748;,
  0.258238;0.204321;0.944228;,
  0.147436;0.141761;0.978860;,
  0.034069;0.076735;0.996469;,
  -0.777967;0.562812;-0.279301;,
  -0.903441;0.424207;0.061998;,
  -0.781958;0.617451;0.085411;,
  0.542731;-0.812084;0.214388;,
  0.764080;0.337449;0.549827;,
  0.268776;0.928177;-0.257385;,
  0.350901;0.909662;-0.222223;,
  0.430105;0.883576;-0.185212;,
  -0.547131;-0.339803;-0.764972;,
  -0.148178;-0.957391;0.247885;,
  -0.054489;-0.971017;0.232715;,
  0.197780;-0.946058;0.256626;,
  0.763847;0.337999;-0.549813;,
  -0.295877;-0.944102;0.145352;,
  -0.210319;-0.960565;0.181882;,
  -0.150549;0.949471;-0.275390;,
  0.180385;0.949271;-0.257575;,
  0.046467;0.065417;0.996776;,
  -0.464948;0.845385;-0.262959;,
  -0.263440;-0.106741;-0.958752;,
  0.877247;-0.469259;-0.101158;,
  0.026699;-0.286316;0.957763;,
  -0.977357;0.208627;0.035320;;
  36;
  4;0,1,4,3;,
  4;26,27,27,26;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;18,19,10,9;,
  4;19,20,11,10;,
  4;33,34,13,12;,
  4;34,35,14,13;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;15,16,23,24;,
  4;16,17,22,23;,
  4;32,32,32,32;,
  4;36,21,37,38;,
  4;15,24,25,39;,
  4;12,40,18,9;,
  4;41,42,19,18;,
  4;42,43,20,19;,
  4;5,21,36,8;,
  4;2,22,44,5;,
  4;23,22,45,46;,
  4;24,23,46,47;,
  4;25,24,0,3;,
  4;18,48,3,6;,
  4;46,2,49,50;,
  4;28,29,30,31;,
  4;51,52,52,51;,
  4;4,1,26,26;,
  4;53,53,53,53;,
  4;51,51,54,54;,
  4;27,27,31,30;,
  4;49,2,28,31;,
  4;44,55,55,55;,
  4;56,56,56,56;,
  4;17,14,57,57;,
  4;37,21,58,58;;
 }
 MeshTextureCoords {
  51;
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.375000;0.125000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.375000;0.374952;,
  0.500000;0.374952;,
  0.500000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.374952;,
  0.625000;0.500000;,
  0.500000;0.625000;,
  0.375000;0.625000;,
  0.625000;0.625000;,
  0.500000;0.750000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.500000;0.875048;,
  0.375000;0.875048;,
  0.625000;0.875048;,
  0.749952;0.125000;,
  0.749952;0.000000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.749953;0.250000;,
  0.749952;0.125000;,
  0.875000;0.125000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.250048;0.000000;,
  0.250048;0.125000;,
  0.125000;0.125000;,
  0.250048;0.250000;,
  0.125000;0.250000;,
  0.625000;0.000000;,
  0.749952;0.000000;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.375000;1.000000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.875000;0.000000;;
 }
}
