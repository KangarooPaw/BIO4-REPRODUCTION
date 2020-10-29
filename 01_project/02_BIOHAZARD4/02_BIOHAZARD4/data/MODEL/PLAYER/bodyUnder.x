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
 54;
 3.06830;1.18780;-2.50090;,
 3.06830;-0.67060;-2.22140;,
 0.00000;0.37600;-2.46390;,
 0.00000;0.96460;-2.89800;,
 -3.06830;1.18780;-2.50090;,
 -3.06830;-0.67060;-2.22140;,
 -4.88950;-0.68210;-1.42070;,
 -4.62580;1.12860;-1.26360;,
 2.72580;4.92430;-2.22140;,
 2.85290;3.14690;-2.69550;,
 0.00000;3.08420;-2.77620;,
 0.00000;4.92430;-2.22140;,
 -2.72580;4.92430;-2.22140;,
 -2.85290;3.14690;-2.69550;,
 -4.31620;3.20790;-1.64990;,
 -3.84260;4.92430;-1.64990;,
 2.08300;5.76220;2.32830;,
 2.72580;6.04610;-0.34100;,
 0.00000;6.04610;-0.34100;,
 0.00000;5.76220;2.32830;,
 -2.08300;5.76220;2.32830;,
 -2.72580;6.04610;-0.34100;,
 -4.11720;4.96050;-0.05810;,
 -3.33920;5.01240;1.74050;,
 0.00000;3.06840;3.81010;,
 2.67970;3.12010;4.06230;,
 -4.33890;3.22660;1.91910;,
 -2.67970;3.12010;4.06230;,
 2.66060;-0.88920;2.37100;,
 2.78330;0.76780;3.50150;,
 0.00000;0.84100;3.35750;,
 0.00000;-0.58310;2.22140;,
 -2.66060;-0.88920;2.37100;,
 -2.78330;0.76780;3.50150;,
 -4.58170;1.00390;1.77190;,
 -4.17400;-0.68210;1.37720;,
 0.00000;-1.85440;-0.02620;,
 3.06830;-1.38780;-0.39470;,
 -4.85790;-0.68210;-0.13640;,
 -3.06830;-1.38780;-0.39470;,
 -4.84330;1.16430;-0.05810;,
 -4.60580;3.21560;-0.05810;,
 4.17400;-0.68210;1.37720;,
 4.85790;-0.68210;-0.13640;,
 4.84330;1.16430;-0.05810;,
 4.58170;1.00390;1.77190;,
 4.33890;3.22660;1.91910;,
 4.60580;3.21560;-0.05810;,
 4.11720;4.96050;-0.05810;,
 3.33920;5.01240;1.74050;,
 4.31620;3.20790;-1.64990;,
 3.84260;4.92430;-1.64990;,
 4.88950;-0.68210;-1.42070;,
 4.62580;1.12860;-1.26360;;
 
 52;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,16,19;,
 4;26,27,20,23;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,28,31;,
 4;38,39,32,35;,
 4;40,38,35,34;,
 4;22,41,26,23;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;42,28,37,43;,
 4;45,29,28,42;,
 4;49,16,25,46;,
 4;48,17,16,49;,
 4;50,9,8,51;,
 4;52,1,0,53;,
 4;31,32,39,36;,
 4;30,33,32,31;,
 4;19,20,27,24;,
 4;18,21,20,19;,
 4;10,13,12,11;,
 4;2,5,4,3;,
 4;51,8,17,48;,
 4;18,17,8,11;,
 4;11,12,21,18;,
 4;22,21,12,15;,
 4;14,41,22,15;,
 4;6,38,40,7;,
 4;5,39,38,6;,
 4;36,39,5,2;,
 4;1,37,36,2;,
 4;43,37,1,52;,
 4;44,43,52,53;,
 4;48,47,50,51;,
 4;53,0,9,50;,
 4;10,9,0,3;,
 4;3,4,13,10;,
 4;14,13,4,7;,
 4;7,40,41,14;,
 4;26,41,40,34;,
 4;33,27,26,34;,
 4;24,27,33,30;,
 4;29,25,24,30;,
 4;46,25,29,45;,
 4;45,44,47,46;,
 4;50,47,44,53;;
 
 MeshMaterialList {
  23;
  52;
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
   0.048000;0.080000;0.104000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/pantufront.png";
   }
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
  0.849223;0.050168;-0.525646;,
  0.000000;-0.646717;-0.762730;,
  -0.849223;0.050168;-0.525646;,
  0.849348;0.045921;-0.525831;,
  0.000000;-0.200653;-0.979662;,
  -0.849348;0.045921;-0.525831;,
  0.716372;0.488325;-0.498346;,
  0.000000;0.609327;-0.792919;,
  -0.716372;0.488325;-0.498346;,
  0.733630;0.575756;0.360959;,
  0.000000;0.841104;0.540873;,
  -0.733630;0.575757;0.360959;,
  0.873289;-0.123171;0.471376;,
  0.000000;-0.413429;0.910536;,
  -0.873289;-0.123171;0.471376;,
  0.816755;-0.277338;0.505959;,
  0.000000;-0.797527;0.603283;,
  -0.707530;-0.556347;0.435751;,
  0.241494;-0.637427;-0.731688;,
  0.234138;-0.791780;0.564149;,
  0.331974;-0.346287;0.877427;,
  0.336064;0.794238;0.506208;,
  0.274329;0.612068;-0.741698;,
  0.336799;-0.109363;-0.935204;,
  -0.208147;-0.456950;-0.864796;,
  -0.234138;-0.791780;0.564149;,
  -0.331974;-0.346287;0.877427;,
  -0.336064;0.794238;0.506208;,
  -0.274329;0.612068;-0.741698;,
  -0.336799;-0.109363;-0.935204;,
  0.785201;0.619162;-0.009859;,
  0.281321;0.949602;-0.138253;,
  0.000000;0.976769;-0.214294;,
  -0.281321;0.949602;-0.138253;,
  -0.785201;0.619162;-0.009859;,
  -0.998384;0.041175;0.039162;,
  -0.289993;-0.957028;0.000958;,
  -0.146280;-0.988136;-0.046788;,
  0.000000;-0.995198;-0.097884;,
  0.146280;-0.988136;-0.046788;,
  0.994795;-0.029576;0.097507;,
  0.998384;0.041175;0.039162;,
  0.827277;0.150324;-0.541309;,
  0.314568;0.114257;-0.942334;,
  0.000000;0.132046;-0.991243;,
  -0.314568;0.114257;-0.942334;,
  -0.827277;0.150324;-0.541309;,
  -0.975105;0.221651;0.006482;,
  -0.867374;0.248290;0.431293;,
  -0.373114;0.216385;0.902200;,
  0.000000;0.157074;0.987587;,
  0.373114;0.216385;0.902200;,
  0.867374;0.248290;0.431293;,
  0.975105;0.221651;0.006482;,
  -0.994795;-0.029576;0.097507;,
  0.304800;-0.934842;0.182121;,
  0.289993;-0.957028;0.000958;,
  -0.265463;-0.947124;-0.180238;,
  0.265463;-0.947124;-0.180238;;
  52;
  4;23,18,1,4;,
  4;29,24,2,5;,
  4;22,43,44,7;,
  4;28,45,46,8;,
  4;21,31,32,10;,
  4;27,33,34,11;,
  4;50,51,21,10;,
  4;48,49,27,11;,
  4;19,20,13,16;,
  4;25,26,14,17;,
  4;38,39,19,16;,
  4;36,37,25,17;,
  4;35,54,17,14;,
  4;34,47,48,11;,
  4;15,40,41,12;,
  4;52,53,30,9;,
  4;55,19,39,56;,
  4;12,20,19,15;,
  4;9,21,51,52;,
  4;30,31,21,9;,
  4;42,43,22,6;,
  4;0,18,23,3;,
  4;16,25,37,38;,
  4;13,26,25,16;,
  4;10,27,49,50;,
  4;32,33,27,10;,
  4;44,45,28,7;,
  4;1,24,29,4;,
  4;6,22,31,30;,
  4;32,31,22,7;,
  4;7,28,33,32;,
  4;34,33,28,8;,
  4;46,47,34,8;,
  4;2,54,35,5;,
  4;57,37,36,57;,
  4;38,37,24,1;,
  4;18,39,38,1;,
  4;56,39,18,58;,
  4;41,40,0,3;,
  4;30,53,42,6;,
  4;3,23,43,42;,
  4;44,43,23,4;,
  4;4,29,45,44;,
  4;46,45,29,5;,
  4;5,35,47,46;,
  4;48,47,35,14;,
  4;26,49,48,14;,
  4;50,49,26,13;,
  4;20,51,50,13;,
  4;52,51,20,12;,
  4;12,41,53,52;,
  4;42,53,41,3;;
 }
 MeshTextureCoords {
  54;
  0.780980;0.376168;,
  0.780980;0.569912;,
  0.500000;0.460801;,
  0.500000;0.399437;,
  0.219020;0.376168;,
  0.219020;0.569912;,
  0.052244;0.571111;,
  0.076392;0.382339;,
  0.749615;-0.013376;,
  0.761255;0.171925;,
  0.500000;0.178461;,
  0.500000;-0.013376;,
  0.250385;-0.013376;,
  0.238745;0.171925;,
  0.104744;0.165565;,
  0.148114;-0.013376;,
  0.690751;-0.100730;,
  0.749615;-0.130327;,
  0.500000;-0.130327;,
  0.500000;-0.100730;,
  0.309249;-0.100730;,
  0.250385;-0.130327;,
  0.122967;-0.017150;,
  0.194212;-0.022560;,
  0.500000;0.180108;,
  0.745394;0.174718;,
  0.102665;0.163616;,
  0.254606;0.174718;,
  0.743645;0.592702;,
  0.754881;0.419954;,
  0.500000;0.412323;,
  0.500000;0.560790;,
  0.256355;0.592702;,
  0.245119;0.419954;,
  0.080430;0.395340;,
  0.117766;0.571111;,
  0.500000;0.693328;,
  0.780980;0.644683;,
  0.055137;0.571111;,
  0.219020;0.644683;,
  0.056474;0.378618;,
  0.078223;0.164762;,
  0.882234;0.571111;,
  0.944863;0.571111;,
  0.943526;0.378618;,
  0.919570;0.395340;,
  0.897335;0.163616;,
  0.921777;0.164762;,
  0.877033;-0.017150;,
  0.805788;-0.022560;,
  0.895256;0.165565;,
  0.851886;-0.013376;,
  0.947756;0.571111;,
  0.923608;0.382339;;
 }
}