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
 75;
 3.82656;0.00920;-1.92852;,
 5.16576;0.00920;-1.95143;,
 5.16285;-1.47664;-1.28121;,
 3.80079;-1.47416;-1.27982;,
 3.84619;1.49256;-1.27982;,
 5.16285;1.49504;-1.28121;,
 3.84619;1.49256;1.28683;,
 5.16285;1.49504;1.28822;,
 5.18096;1.97698;0.17391;,
 3.83591;1.89669;0.17391;,
 3.82656;0.00920;1.93552;,
 5.16576;0.00920;1.95843;,
 3.80079;-1.47416;1.28683;,
 5.16285;-1.47664;1.28822;,
 3.81318;-1.87830;0.17391;,
 5.14780;-1.95859;0.17391;,
 0.96854;-1.23535;1.03520;,
 0.41104;0.00920;1.48277;,
 -1.09957;0.00920;0.01496;,
 0.40716;-1.43312;0.01496;,
 0.96854;1.25375;1.03520;,
 0.40716;1.45151;0.01496;,
 3.80079;-1.47416;-1.27982;,
 5.16285;-1.47664;-1.28121;,
 0.41104;0.00920;-1.45285;,
 0.96854;-1.23535;-1.00528;,
 0.96854;1.25375;-1.00528;,
 0.40716;-1.43312;0.01496;,
 0.96854;-1.23535;-1.00528;,
 3.61197;-1.23989;-1.00753;,
 3.62604;-1.58021;0.01496;,
 0.96854;-1.23535;1.03520;,
 3.61197;-1.23989;1.03745;,
 0.41104;0.00920;1.48277;,
 3.64123;0.00920;1.51983;,
 0.96854;1.25375;1.03520;,
 3.66352;1.25830;1.03745;,
 0.40716;1.45151;0.01496;,
 3.65184;1.59860;0.01496;,
 3.66352;1.25830;-1.00753;,
 3.64123;0.00920;-1.48991;,
 3.61197;-1.23989;-1.00753;,
 5.43107;-1.07174;-0.90320;,
 5.43392;0.00920;-1.33376;,
 5.43107;1.09014;-0.90320;,
 5.44884;1.44075;-0.01895;,
 5.43107;1.09014;0.94216;,
 5.43392;0.00920;1.37272;,
 5.43107;-1.07174;0.94216;,
 5.41630;-1.42235;-0.01895;,
 5.43107;-1.07174;-0.90320;,
 4.85347;-1.11508;-0.70784;,
 4.85347;-0.05708;-1.20281;,
 9.27427;-0.05708;-0.85771;,
 8.49218;-0.81530;-0.70784;,
 4.85347;1.00092;-0.70784;,
 8.49218;0.70115;-0.70784;,
 4.42088;1.31165;0.13472;,
 4.85347;0.99681;0.97792;,
 8.62940;0.67431;0.97792;,
 9.09236;0.96126;0.13472;,
 4.85347;-0.05708;1.37795;,
 9.15119;-0.05708;1.15916;,
 4.85347;-1.11096;0.97792;,
 8.62940;-0.78848;0.97792;,
 4.42088;-1.42581;0.13472;,
 9.09236;-1.07541;0.13472;,
 9.98724;-0.05708;0.13472;,
 9.15119;-0.05708;1.15916;,
 8.62940;-0.78848;0.97792;,
 9.09236;-1.07541;0.13472;,
 9.09236;0.96126;0.13472;,
 8.62940;0.67431;0.97792;,
 4.85347;-1.11508;-0.70784;,
 8.49218;-0.81530;-0.70784;;
 
 48;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,8,9;,
 4;10,11,7,6;,
 4;12,13,11,10;,
 4;14,15,13,12;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;9,8,5,4;,
 4;22,23,15,14;,
 4;18,24,25,19;,
 4;21,26,24,18;,
 4;27,28,29,30;,
 4;31,27,30,32;,
 4;33,31,32,34;,
 4;35,33,34,36;,
 4;37,35,36,38;,
 4;26,37,38,39;,
 4;24,26,39,40;,
 4;25,24,40,41;,
 4;40,0,3,41;,
 4;42,2,1,43;,
 4;39,4,0,40;,
 4;43,1,5,44;,
 4;36,6,9,38;,
 4;45,8,7,46;,
 4;34,10,6,36;,
 4;46,7,11,47;,
 4;32,12,10,34;,
 4;47,11,13,48;,
 4;30,14,12,32;,
 4;48,13,15,49;,
 4;38,9,4,39;,
 4;44,5,8,45;,
 4;29,22,14,30;,
 4;49,15,23,50;,
 4;51,52,53,54;,
 4;52,55,56,53;,
 4;57,58,59,60;,
 4;58,61,62,59;,
 4;61,63,64,62;,
 4;63,65,66,64;,
 4;67,68,69,70;,
 4;71,72,68,67;,
 4;55,57,60,56;,
 4;53,56,71,67;,
 4;54,53,67,70;,
 4;65,73,74,66;;
 
 MeshMaterialList {
  23;
  48;
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  2,
  2,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  0;;
  Material {
   0.800000;0.727843;0.608627;1.000000;;
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
  70;
  -0.255195;-0.706422;-0.660185;,
  0.901177;-0.324822;-0.287002;,
  0.910093;-0.000000;-0.414405;,
  -0.352046;-0.486581;-0.799564;,
  0.899290;0.320092;-0.298024;,
  -0.255124;0.706461;-0.660170;,
  -0.262665;0.942862;0.204981;,
  0.899134;0.437673;0.000006;,
  0.903446;0.299542;0.306693;,
  -0.255124;0.706461;0.660170;,
  0.900983;-0.000000;0.433854;,
  -0.256237;-0.213379;0.942768;,
  0.904740;-0.306746;0.295555;,
  -0.255195;-0.706422;0.660185;,
  0.894804;-0.446459;-0.000245;,
  -0.363049;-0.822631;0.437577;,
  -0.642865;-0.545504;0.537727;,
  -0.347727;-0.757331;-0.552753;,
  -0.331731;-0.941505;-0.059353;,
  -0.016490;-0.738285;0.674288;,
  -0.006503;0.000013;0.999979;,
  -0.016373;0.738323;0.674248;,
  -0.335506;0.939841;-0.064305;,
  -0.350640;0.752049;-0.558099;,
  -0.006503;0.000013;-0.999979;,
  -0.009483;0.000060;-0.999955;,
  -0.345583;-0.763696;-0.545290;,
  -0.020981;-0.748748;-0.662523;,
  -0.348529;0.758683;-0.550389;,
  -0.020929;0.748990;-0.662251;,
  -0.020066;0.720996;0.692648;,
  -0.345208;0.937873;-0.035006;,
  -0.030625;0.998676;0.041323;,
  -0.009482;0.000060;0.999955;,
  -0.020109;-0.720698;0.692957;,
  -0.513020;-0.858048;0.023748;,
  -0.030809;-0.998668;0.041389;,
  0.071543;-0.713160;-0.697341;,
  0.266044;-0.703578;-0.658937;,
  0.058788;-0.000002;-0.998271;,
  0.272727;0.239177;-0.931887;,
  0.071541;0.713159;-0.697343;,
  0.266045;0.703576;-0.658939;,
  0.063821;0.695909;0.715288;,
  0.278148;0.680078;0.678328;,
  0.041755;-0.000001;0.999128;,
  0.412701;-0.000002;0.910867;,
  0.063821;-0.695911;0.715286;,
  0.278148;-0.680080;0.678325;,
  0.079184;0.996833;0.007347;,
  0.408137;0.912901;0.006073;,
  0.629851;-0.568645;0.529084;,
  0.296610;-0.932370;0.206659;,
  0.079185;-0.996833;0.007345;,
  -0.642866;0.545504;0.537725;,
  -0.642865;-0.545504;-0.537727;,
  -0.363049;-0.822631;-0.437577;,
  -0.642866;0.545504;-0.537725;,
  -0.352040;0.486594;-0.799558;,
  -0.905888;0.012829;-0.423323;,
  -0.891218;-0.156177;-0.425840;,
  -0.894483;0.181465;-0.408622;,
  -0.892910;0.333318;0.302673;,
  -0.867940;0.466172;0.171361;,
  -0.897099;0.012154;0.441662;,
  -0.890747;-0.332806;0.309533;,
  -0.859910;-0.485255;0.158374;,
  0.629852;0.568641;0.529087;,
  0.590732;0.614785;-0.522565;,
  0.590728;-0.614791;-0.522564;;
  48;
  4;25,25,27,26;,
  4;28,29,25,25;,
  4;30,30,32,31;,
  4;33,33,30,30;,
  4;34,34,33,33;,
  4;35,36,34,34;,
  4;13,11,16,15;,
  4;54,9,6,54;,
  4;31,32,29,28;,
  4;26,27,36,35;,
  4;55,3,0,56;,
  4;57,5,58,57;,
  4;56,0,17,18;,
  4;13,15,18,19;,
  4;11,13,19,20;,
  4;9,11,20,21;,
  4;6,9,21,22;,
  4;5,6,22,23;,
  4;58,5,23,24;,
  4;0,3,24,17;,
  4;59,59,60,60;,
  4;1,1,2,2;,
  4;61,61,59,59;,
  4;2,2,4,4;,
  4;62,62,63,63;,
  4;7,7,8,8;,
  4;64,64,62,62;,
  4;8,8,10,10;,
  4;65,65,64,64;,
  4;10,10,12,12;,
  4;66,35,65,65;,
  4;12,12,14,14;,
  4;22,31,28,23;,
  4;4,4,7,7;,
  4;17,26,35,18;,
  4;14,14,1,1;,
  4;37,39,40,38;,
  4;39,41,42,40;,
  4;49,43,44,50;,
  4;43,45,46,44;,
  4;45,47,48,46;,
  4;47,53,52,48;,
  4;51,46,48,52;,
  4;50,44,46,67;,
  4;41,49,50,42;,
  4;40,42,50,68;,
  4;38,69,69,69;,
  4;53,37,38,52;;
 }
 MeshTextureCoords {
  75;
  0.460636;0.125000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.460636;0.000000;,
  0.460636;0.250000;,
  0.500000;0.250000;,
  0.460636;0.500000;,
  0.500000;0.500000;,
  0.500000;0.371798;,
  0.460636;0.371798;,
  0.460636;0.625000;,
  0.500000;0.625000;,
  0.460636;0.750000;,
  0.500000;0.750000;,
  0.460636;0.878202;,
  0.500000;0.878202;,
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.253202;0.125000;,
  0.253202;0.000000;,
  0.125000;0.250000;,
  0.253202;0.250000;,
  0.460636;1.000000;,
  0.500000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.878202;,
  0.375000;1.000000;,
  0.460636;1.000000;,
  0.460636;0.878202;,
  0.375000;0.750000;,
  0.460636;0.750000;,
  0.375000;0.625000;,
  0.460636;0.625000;,
  0.375000;0.500000;,
  0.460636;0.500000;,
  0.375000;0.371798;,
  0.460636;0.371798;,
  0.460636;0.250000;,
  0.460636;0.125000;,
  0.460636;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.500000;0.371798;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.878202;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.500000;0.371798;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.371798;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.500000;0.878202;,
  0.625000;0.878202;,
  0.746798;0.125000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.746798;0.000000;,
  0.746798;0.250000;,
  0.875000;0.250000;,
  0.500000;1.000000;,
  0.625000;1.000000;;
 }
}