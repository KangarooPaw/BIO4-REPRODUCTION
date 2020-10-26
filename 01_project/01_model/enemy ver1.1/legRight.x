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
 92;
 -1.28637;-19.43761;-4.96058;,
 -1.43437;-18.85592;-5.71828;,
 0.13763;-18.71982;-5.81038;,
 0.13763;-19.43761;-5.30288;,
 1.70963;-18.67362;-5.08828;,
 1.49643;-19.43761;-4.36378;,
 -1.29027;-17.72212;-4.87048;,
 0.13763;-17.68432;-4.97288;,
 1.56563;-17.72212;-4.02258;,
 -1.22627;-16.93132;-2.11578;,
 -1.22627;-16.94082;1.00082;,
 0.13763;-16.08952;1.30062;,
 0.13763;-17.02722;-2.11578;,
 1.50153;-16.94082;1.00082;,
 1.50153;-17.23872;-2.11578;,
 -1.43437;-18.31262;1.36282;,
 0.13763;-18.31262;2.11252;,
 1.51853;-18.31262;1.36282;,
 1.50153;-16.94082;1.00082;,
 -1.14887;-19.43761;1.01852;,
 0.13763;-19.43761;1.65912;,
 1.10323;-19.43761;1.01852;,
 -0.99247;-19.43761;-2.11578;,
 0.13763;-19.43761;-2.11578;,
 1.46873;-19.43761;-2.11578;,
 1.70963;-18.31262;-2.11578;,
 1.51853;-18.31262;1.36282;,
 1.10323;-19.43761;1.01852;,
 1.46873;-19.43761;-2.11578;,
 -1.67897;-18.31262;-2.11578;,
 1.92073;-18.70382;-4.23538;,
 -1.72807;-18.87432;-5.10488;,
 -1.86697;-14.80521;-1.40218;,
 -1.46317;-8.47671;-1.21708;,
 -0.03297;-8.47671;-1.63518;,
 -0.03297;-14.72361;-2.27768;,
 1.39733;-8.47671;-1.21708;,
 1.80103;-14.76471;-1.40218;,
 -1.52117;-0.77620;-1.03018;,
 -0.03297;0.14859;-1.78168;,
 1.45523;-0.77620;-1.03018;,
 -1.81897;-0.02100;0.03992;,
 -1.38687;-0.07811;0.88712;,
 -0.03297;0.88039;1.95792;,
 -0.03297;1.23880;0.13272;,
 1.32093;-0.07811;0.88712;,
 1.75313;-0.02100;0.03992;,
 -1.46317;-8.47671;1.25142;,
 -0.03297;-8.47671;1.83672;,
 1.39733;-8.47671;1.25142;,
 -1.73617;-14.52301;1.67822;,
 -0.03297;-14.48501;2.60742;,
 1.67023;-14.52301;1.67822;,
 -0.81757;-16.82292;0.92992;,
 -1.11177;-17.47862;0.03992;,
 -0.03297;-18.36222;0.13272;,
 -0.03297;-17.47862;1.42982;,
 1.04593;-17.47862;0.03992;,
 0.75173;-16.82292;0.92992;,
 1.74233;-8.47671;0.03992;,
 2.21743;-14.69231;-0.05718;,
 -1.80827;-8.47671;0.03992;,
 -2.28327;-14.74821;-0.05718;,
 -0.03297;-17.47862;-1.05288;,
 0.85243;-17.04022;-0.53278;,
 -0.91827;-17.04022;-0.53278;,
 -1.03557;-15.19791;-0.67998;,
 -0.03297;-15.24932;-1.17808;,
 0.96963;-15.17971;-0.67998;,
 1.19573;-15.16841;0.03992;,
 0.89063;-15.02741;0.99912;,
 -0.03297;-15.00121;1.51732;,
 -0.95647;-15.02741;0.99912;,
 -1.26167;-15.26031;0.03992;,
 -0.91827;-17.04022;-0.53278;,
 -1.03557;-15.19791;-0.67998;,
 -0.03297;-15.24932;-1.17808;,
 -0.03297;-17.47862;-1.05288;,
 0.96963;-15.17971;-0.67998;,
 0.85243;-17.04022;-0.53278;,
 1.19573;-15.16841;0.03992;,
 1.04593;-17.47862;0.03992;,
 0.89063;-15.02741;0.99912;,
 0.75173;-16.82292;0.92992;,
 -0.03297;-15.00121;1.51732;,
 -0.03297;-17.47862;1.42982;,
 0.75173;-16.82292;0.92992;,
 0.89063;-15.02741;0.99912;,
 -0.95647;-15.02741;0.99912;,
 -0.81757;-16.82292;0.92992;,
 -1.26167;-15.26031;0.03992;,
 -1.11177;-17.47862;0.03992;;
 
 68;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;1,6,7,2;,
 4;2,7,8,4;,
 4;9,10,11,12;,
 4;12,11,13,14;,
 4;10,15,16,11;,
 4;11,16,17,18;,
 4;15,19,20,16;,
 4;16,20,21,17;,
 4;19,22,23,20;,
 4;20,23,24,21;,
 4;25,26,27,28;,
 4;14,13,26,25;,
 4;19,15,29,22;,
 4;15,10,9,29;,
 4;6,9,12,7;,
 4;7,12,14,8;,
 4;8,14,25,30;,
 4;5,30,25,28;,
 4;23,3,5,28;,
 4;22,0,3,23;,
 3;31,1,0;,
 3;6,1,31;,
 4;9,6,31,29;,
 4;29,31,0,22;,
 3;4,8,30;,
 3;5,4,30;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;33,38,39,34;,
 4;34,39,40,36;,
 4;41,42,43,44;,
 4;44,43,45,46;,
 4;42,47,48,43;,
 4;43,48,49,45;,
 4;47,50,51,48;,
 4;48,51,52,49;,
 4;53,54,55,56;,
 4;56,55,57,58;,
 4;59,49,52,60;,
 4;46,45,49,59;,
 4;50,47,61,62;,
 4;47,42,41,61;,
 4;38,41,44,39;,
 4;39,44,46,40;,
 4;36,40,46,59;,
 4;37,36,59,60;,
 4;55,63,64,57;,
 4;54,65,63,55;,
 4;61,33,32,62;,
 4;41,38,33,61;,
 4;66,32,35,67;,
 4;67,35,37,68;,
 4;68,37,60,69;,
 4;52,70,69,60;,
 4;51,71,70,52;,
 4;50,72,71,51;,
 4;72,50,62,73;,
 4;32,66,73,62;,
 4;74,75,76,77;,
 4;77,76,78,79;,
 4;79,78,80,81;,
 4;82,83,81,80;,
 4;84,85,86,87;,
 4;88,89,85,84;,
 4;89,88,90,91;,
 4;75,74,91,90;;
 
 MeshMaterialList {
  14;
  68;
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  5,
  5,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  5,
  5,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
  Material {
   0.793600;0.787200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/zombieskin.png";
   }
  }
  Material {
   0.523922;0.473726;0.257255;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.577255;0.577255;0.087843;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.169412;0.169412;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/zombieskin.png";
   }
  }
  Material {
   0.545882;0.389020;0.235294;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/eye.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.771765;0.759216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/met.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/beruto.png";
   }
  }
  Material {
   0.072000;0.024000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.064000;0.072000;0.040000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.545600;0.388800;0.235200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/eye.jpg";
   }
  }
  Material {
   0.800000;0.771765;0.759216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/hukufrontenemy.png";
   }
  }
  Material {
   0.800000;0.771765;0.759216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/hukubackenemy.png";
   }
  }
  Material {
   0.800000;0.320000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  104;
  -0.462445;-0.841713;-0.278683;,
  0.089147;-0.917855;-0.386774;,
  0.646842;-0.720879;-0.248855;,
  -0.408483;-0.713376;-0.569418;,
  0.165565;-0.675722;-0.718323;,
  0.664412;-0.568873;-0.484706;,
  -0.557200;0.699566;-0.447365;,
  0.120236;0.850670;-0.511765;,
  0.532153;0.740656;-0.410172;,
  -0.214146;0.969330;-0.120588;,
  0.055439;0.987291;-0.148937;,
  0.320932;0.932389;-0.166295;,
  -0.428666;-0.025448;0.903104;,
  0.027795;-0.044572;0.998619;,
  0.848516;-0.082657;0.522674;,
  -0.759915;-0.428381;0.488896;,
  0.037294;-0.406147;0.913047;,
  0.793529;-0.366339;0.485908;,
  -0.101543;0.977038;-0.187311;,
  0.071554;0.978001;-0.195942;,
  0.241687;0.949795;-0.198689;,
  0.996364;-0.070736;0.047496;,
  0.000000;-1.000000;-0.000000;,
  -0.306617;-0.951012;0.039526;,
  -0.994426;-0.102283;0.025575;,
  -0.780768;-0.612068;-0.125592;,
  0.994059;-0.049292;-0.097044;,
  -0.711866;-0.285439;-0.641694;,
  0.537542;-0.375208;-0.755161;,
  0.713315;-0.284802;-0.640367;,
  -0.738094;0.042337;-0.673368;,
  -0.000140;0.042589;-0.999093;,
  0.737926;0.042539;-0.673540;,
  -0.721990;0.249743;-0.645259;,
  -0.000005;0.003209;-0.999995;,
  0.721982;0.249740;-0.645269;,
  -0.773411;0.298530;0.559210;,
  -0.633201;0.444478;0.633637;,
  0.773400;0.298531;0.559224;,
  -0.758789;0.050874;0.649347;,
  -0.184811;0.077700;0.979698;,
  0.758619;0.050939;0.649540;,
  -0.756236;-0.243137;0.607447;,
  -0.619961;-0.319055;0.716835;,
  0.757301;-0.242842;0.606236;,
  -0.906280;0.420165;-0.046015;,
  -0.632629;0.762099;-0.137788;,
  0.906280;0.420166;-0.046013;,
  0.998886;0.038817;0.026826;,
  0.835102;-0.328842;0.440986;,
  -0.656724;-0.555777;0.509730;,
  -0.945681;-0.262596;0.191654;,
  -0.998899;0.038594;0.026666;,
  -0.732520;0.083369;-0.675622;,
  -0.000274;0.081795;-0.996649;,
  0.732174;0.083770;-0.675947;,
  0.997363;0.072565;0.001280;,
  0.757642;0.088929;0.646584;,
  -0.000006;0.107483;0.994207;,
  -0.757982;0.088807;0.646202;,
  -0.997396;0.072116;0.000969;,
  -0.291498;-0.922345;-0.253591;,
  0.015680;-0.924804;-0.380121;,
  0.310538;-0.918603;-0.244405;,
  0.412679;-0.907954;0.072903;,
  0.312963;-0.890317;0.330742;,
  -0.000002;-0.904134;0.427248;,
  -0.615227;-0.553771;0.561100;,
  -0.415026;-0.906698;0.075181;,
  -0.510636;0.562041;-0.650662;,
  0.143389;0.653945;-0.742830;,
  0.685143;0.555694;-0.470939;,
  -0.399866;0.303360;0.864916;,
  0.014703;0.317193;0.948247;,
  0.426641;0.274247;0.861839;,
  0.943304;-0.322585;0.078214;,
  0.982369;0.186461;0.013504;,
  0.993875;0.108965;0.018401;,
  -0.996248;-0.082776;0.025253;,
  -0.917695;-0.397083;0.012683;,
  -0.970078;0.240233;0.035168;,
  -0.957063;0.289608;-0.012541;,
  0.964810;0.262808;0.008525;,
  -0.899983;0.372112;-0.227075;,
  0.632624;0.762104;-0.137787;,
  0.633185;0.444478;0.633653;,
  0.502029;0.016837;0.864687;,
  0.619920;-0.319073;0.716862;,
  0.656684;-0.555810;0.509746;,
  -0.569616;0.654183;-0.497577;,
  0.569606;0.654174;-0.497599;,
  0.531088;-0.636974;-0.558758;,
  0.791712;-0.381136;-0.477417;,
  -0.531124;-0.636953;-0.558747;,
  -0.537184;-0.375436;-0.755302;,
  -0.312833;-0.880447;0.356299;,
  -0.761326;-0.078818;-0.643561;,
  0.000386;-0.084085;-0.996459;,
  0.763276;-0.077607;-0.641395;,
  0.997047;-0.076762;0.002196;,
  0.774858;-0.065368;0.628747;,
  0.520983;-0.050336;0.852082;,
  -0.521027;-0.050337;0.852055;,
  -0.996905;-0.078592;0.002099;;
  68;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;69,6,7,70;,
  4;70,7,8,71;,
  4;18,9,10,19;,
  4;19,10,11,20;,
  4;72,12,13,73;,
  4;73,13,14,74;,
  4;12,15,16,13;,
  4;13,16,17,14;,
  4;22,23,22,22;,
  4;22,22,22,22;,
  4;21,14,17,75;,
  4;76,77,14,21;,
  4;15,78,24,79;,
  4;78,80,81,24;,
  4;6,18,19,7;,
  4;7,19,20,8;,
  4;82,76,21,26;,
  4;2,26,21,75;,
  4;22,1,2,22;,
  4;23,0,1,22;,
  3;25,3,0;,
  3;6,69,83;,
  4;81,6,83,24;,
  4;24,25,0,23;,
  3;71,8,26;,
  3;2,5,26;,
  4;53,30,31,54;,
  4;54,31,32,55;,
  4;30,33,34,31;,
  4;31,34,35,32;,
  4;45,36,37,46;,
  4;84,85,38,47;,
  4;36,39,40,37;,
  4;85,86,41,38;,
  4;39,59,58,40;,
  4;40,58,57,41;,
  4;42,51,50,43;,
  4;87,88,49,44;,
  4;48,41,57,56;,
  4;47,38,41,48;,
  4;59,39,52,60;,
  4;39,36,45,52;,
  4;33,45,46,89;,
  4;90,84,47,35;,
  4;32,35,47,48;,
  4;55,32,48,56;,
  4;91,28,29,92;,
  4;93,27,94,93;,
  4;52,30,53,60;,
  4;45,33,30,52;,
  4;61,61,62,62;,
  4;62,62,63,63;,
  4;63,63,64,64;,
  4;65,65,64,64;,
  4;66,66,65,65;,
  4;95,67,66,66;,
  4;67,95,68,68;,
  4;61,61,68,68;,
  4;27,96,97,94;,
  4;28,97,98,29;,
  4;29,98,99,92;,
  4;100,44,49,99;,
  4;101,87,44,100;,
  4;67,42,43,102;,
  4;42,67,103,51;,
  4;96,27,51,103;;
 }
 MeshTextureCoords {
  92;
  0.537914;1.706351;,
  0.535899;1.670249;,
  0.493295;1.661803;,
  0.493451;1.706351;,
  0.445680;1.658935;,
  0.445607;1.706351;,
  0.538838;1.599883;,
  0.493569;1.597537;,
  0.439474;1.599883;,
  0.585916;1.550803;,
  0.839203;1.551393;,
  0.984398;1.498559;,
  0.496137;1.556755;,
  0.137509;1.551393;,
  0.403735;1.569882;,
  0.852427;1.636531;,
  0.987189;1.636531;,
  1.114214;1.636531;,
  1.137509;1.551393;,
  0.844767;1.706351;,
  0.985967;1.706351;,
  1.107386;1.706351;,
  0.573183;1.706351;,
  0.496137;1.706351;,
  1.405535;1.706351;,
  0.392887;1.636531;,
  0.114214;1.636531;,
  0.107386;1.706351;,
  0.405535;1.706351;,
  0.607120;1.636531;,
  0.430154;1.660810;,
  0.549062;1.671391;,
  0.329873;2.333353;,
  0.366669;1.756671;,
  0.496996;1.756671;,
  0.496996;2.325917;,
  0.627331;1.756671;,
  0.664118;2.329662;,
  0.361384;1.054967;,
  0.496996;0.970695;,
  0.632607;1.054967;,
  0.334247;0.986149;,
  0.373622;0.991353;,
  0.496996;0.904010;,
  0.496996;0.871351;,
  0.620369;0.991353;,
  0.659753;0.986149;,
  0.366669;1.756671;,
  0.496996;1.756671;,
  0.627331;1.756671;,
  0.341792;2.307637;,
  0.496996;2.304174;,
  0.652199;2.307637;,
  0.545377;3.261050;,
  0.589079;3.354641;,
  0.428829;3.480762;,
  0.428829;3.354641;,
  0.268565;3.354641;,
  0.312267;3.261050;,
  0.658769;1.756671;,
  0.702062;2.323065;,
  0.335222;1.756671;,
  0.291938;2.328158;,
  0.428829;3.354641;,
  0.297308;3.292067;,
  0.560335;3.292067;,
  0.405634;2.369137;,
  0.496996;2.373821;,
  0.588357;2.367479;,
  0.608960;2.366449;,
  0.581158;2.353601;,
  0.496996;2.351213;,
  0.412842;2.353601;,
  0.385031;2.374824;,
  0.670742;1.557562;,
  0.661436;1.443224;,
  0.522359;1.446414;,
  0.525903;1.584771;,
  0.356537;1.442094;,
  0.350305;1.557562;,
  0.235308;1.441393;,
  0.234187;1.584771;,
  0.088242;1.432642;,
  0.077262;1.544076;,
  0.967719;1.431016;,
  0.966278;1.584771;,
  1.077262;1.544076;,
  1.088242;1.432642;,
  0.855269;1.432642;,
  0.859737;1.544076;,
  0.746021;1.447096;,
  0.746520;1.584771;;
 }
}
