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
 235;
 0.97550;12.88223;-1.02180;,
 0.00000;12.49183;-1.52900;,
 0.00000;14.85153;-1.49040;,
 0.97550;14.85153;-0.72220;,
 -0.97550;12.88223;-1.02180;,
 -0.97550;14.85153;-0.72220;,
 0.00000;17.08253;-1.22950;,
 0.80530;16.75483;-0.72220;,
 -0.80530;16.75483;-0.72220;,
 0.97550;16.99923;0.11050;,
 0.00000;17.38123;-0.16050;,
 0.00000;16.75483;1.06570;,
 0.97550;16.75483;0.79280;,
 -0.97550;16.99923;0.11050;,
 -0.97550;16.75483;0.79280;,
 0.00000;14.85153;1.48760;,
 0.97550;14.85153;1.10610;,
 -0.97550;14.85153;1.10610;,
 0.00000;12.82973;1.48760;,
 0.97550;12.94823;1.37890;,
 -0.97550;12.94823;1.37890;,
 0.00000;11.92183;-0.17460;,
 2.01960;12.28413;0.09640;,
 -2.01960;12.28413;0.09640;,
 -1.28700;14.85153;0.25640;,
 1.28700;14.85153;0.25640;,
 2.78190;13.02983;-1.36720;,
 2.78190;10.19703;-3.11920;,
 0.00000;10.60323;-3.05420;,
 0.00000;12.58033;-2.02740;,
 2.76000;13.56983;1.85510;,
 2.78190;13.61973;0.27590;,
 0.00000;14.44042;0.08120;,
 0.00000;13.43123;2.08820;,
 0.00000;10.68243;2.52000;,
 2.80210;10.70013;2.18470;,
 -2.78190;13.56983;1.85510;,
 -2.80210;10.70013;2.18470;,
 -2.78190;13.61973;0.27590;,
 -2.78190;10.19703;-3.11920;,
 -2.78190;13.02983;-1.36720;,
 2.78190;9.03503;-3.28850;,
 0.00000;9.03503;-3.19130;,
 -2.78190;9.03503;-3.28850;,
 -2.78190;9.03503;2.39480;,
 0.00000;9.03503;2.59520;,
 2.78190;9.03503;2.39480;,
 0.00000;6.53160;-2.86000;,
 2.90280;6.53160;-2.42610;,
 2.47190;4.19080;-2.42670;,
 0.00000;4.19080;-2.73630;,
 -3.66080;6.53160;-1.73530;,
 -2.90280;6.53160;-2.42610;,
 -2.47190;4.19080;-2.42670;,
 -3.63250;4.19080;-1.71380;,
 1.08890;11.57360;-2.70850;,
 3.11780;10.36010;-3.49580;,
 0.00000;9.29790;-3.56680;,
 0.00000;9.44110;-3.65660;,
 -1.08890;11.57360;-2.70850;,
 -3.11780;10.36010;-3.49580;,
 -4.46470;13.25590;-1.54080;,
 -2.04730;13.71000;1.87630;,
 -2.12770;13.86640;0.10280;,
 -5.36340;13.64210;0.39570;,
 -5.17560;13.65940;1.96610;,
 0.00000;10.90400;2.82430;,
 3.14040;10.92390;2.44840;,
 2.02270;13.71000;1.87630;,
 0.00000;12.84000;2.34030;,
 -5.09390;10.91300;2.13500;,
 -3.14040;10.92390;2.44840;,
 0.00000;4.19080;3.13070;,
 2.59480;4.19080;2.50350;,
 2.90280;6.53160;2.27330;,
 0.00000;6.53160;2.79960;,
 -3.90350;4.19080;1.29010;,
 -2.59480;4.19080;2.50350;,
 -2.90280;6.53160;2.27330;,
 -3.93500;6.53160;1.28160;,
 -4.37500;6.53160;0.05040;,
 -4.23620;4.19080;0.07520;,
 -6.19780;13.17850;0.51760;,
 -6.84530;11.07420;0.32870;,
 -6.20990;11.42180;1.82260;,
 -5.90640;12.99170;1.72910;,
 3.90350;4.19080;1.29010;,
 4.23620;4.19080;0.07520;,
 4.37500;6.53160;0.05040;,
 3.93500;6.53160;1.28160;,
 6.20990;11.42180;1.82260;,
 6.84530;11.07420;0.32870;,
 6.19780;13.17850;0.51760;,
 5.90640;12.99170;1.72910;,
 5.17560;13.65940;1.96610;,
 5.09390;10.91300;2.13500;,
 5.36340;13.64210;0.39570;,
 2.12770;13.86640;0.10280;,
 4.46470;13.25590;-1.54080;,
 4.66960;10.80860;-1.46670;,
 4.55710;13.30110;-1.50690;,
 4.81100;13.42530;-1.35820;,
 3.63250;4.19080;-1.71380;,
 3.66080;6.53160;-1.73530;,
 5.36340;13.64210;0.39570;,
 2.12770;13.86640;0.10280;,
 2.26550;13.50020;-1.46100;,
 -4.55710;13.30110;-1.50690;,
 -2.26550;13.50020;-1.46100;,
 -5.87710;11.44430;-1.05380;,
 -6.84530;11.07420;0.32870;,
 -6.19780;13.17850;0.51760;,
 -5.69950;13.19350;-0.75060;,
 -4.23620;4.19080;0.07520;,
 -4.37500;6.53160;0.05040;,
 4.37500;6.53160;0.05040;,
 4.23620;4.19080;0.07520;,
 6.19780;13.17850;0.51760;,
 6.84530;11.07420;0.32870;,
 5.87710;11.44430;-1.05380;,
 5.69950;13.19350;-0.75060;,
 4.11430;9.05780;-1.75850;,
 3.11780;9.05780;-3.68550;,
 0.00000;9.05780;-3.57650;,
 -3.11780;9.05780;-3.68550;,
 -4.66960;10.80860;-1.46670;,
 -4.11430;9.05780;-1.75850;,
 -4.85340;9.05780;0.02370;,
 -5.25760;9.76760;0.02370;,
 -5.25760;9.76760;0.02370;,
 -4.85340;9.05780;0.02370;,
 -4.34920;9.05780;1.83340;,
 -3.11780;9.05780;2.68390;,
 0.00000;9.05780;2.87360;,
 3.11780;9.05780;2.68390;,
 4.34920;9.05780;1.83340;,
 4.85340;9.05780;0.02370;,
 5.25760;9.76760;0.02370;,
 5.25760;9.76760;0.02370;,
 4.85340;9.05780;0.02370;,
 -5.36340;13.64210;0.39570;,
 -4.81100;13.42530;-1.35820;,
 -2.12770;13.86640;0.10280;,
 2.66120;2.47450;-2.84590;,
 0.00000;2.47450;-3.31710;,
 -2.66120;2.47450;-2.84590;,
 -4.38630;2.47450;-1.76070;,
 0.00000;2.47770;3.95380;,
 2.30610;2.47770;3.43520;,
 -3.85420;2.41380;2.81170;,
 -2.30610;2.47770;3.43520;,
 -4.75170;2.47450;0.96250;,
 3.85420;2.41380;2.81170;,
 4.75170;2.47450;0.96250;,
 4.38630;2.47450;-1.76070;,
 -4.75170;2.47450;0.96250;,
 4.75170;2.47450;0.96250;,
 0.00000;1.72420;-3.05100;,
 2.65890;1.72420;-2.61420;,
 2.65890;0.34520;-2.61420;,
 0.00000;0.34520;-3.05100;,
 -4.19620;1.72420;-1.60850;,
 -2.65890;1.72420;-2.61420;,
 -2.65890;0.34520;-2.61420;,
 -4.19620;0.34520;-1.60850;,
 2.34240;1.72690;3.20700;,
 0.00000;1.72690;3.68770;,
 0.00000;0.34790;3.68770;,
 2.34240;0.34790;3.20700;,
 -2.34240;1.72690;3.20700;,
 -3.72210;1.67280;2.62920;,
 -3.72210;0.29370;2.62920;,
 -2.34240;0.34790;3.20700;,
 -4.52190;1.72420;0.91530;,
 -4.52190;0.34520;0.91530;,
 4.52190;1.72420;0.91530;,
 3.72210;1.67280;2.62920;,
 3.72210;0.29370;2.62920;,
 4.52190;0.34520;0.91530;,
 4.19620;1.72420;-1.60850;,
 4.19620;0.34520;-1.60850;,
 -4.52190;1.72420;0.91530;,
 -4.52190;0.34520;0.91530;,
 4.52190;1.72420;0.91530;,
 4.52190;0.34520;0.91530;,
 2.53100;0.28770;-2.42460;,
 0.00000;0.28770;-2.83310;,
 -2.53100;0.28770;-2.42460;,
 -3.87120;0.28770;-1.48390;,
 0.00000;0.29090;3.46980;,
 2.25510;0.29090;3.02020;,
 -3.45790;0.22700;2.47980;,
 -2.25510;0.29090;3.02020;,
 -4.15520;0.28770;0.87670;,
 3.45790;0.22700;2.47980;,
 4.15520;0.28770;0.87670;,
 3.87120;0.28770;-1.48390;,
 -4.15520;0.28770;0.87670;,
 4.15520;0.28770;0.87670;,
 1.71890;11.84420;-3.11990;,
 0.00000;9.87590;-3.52750;,
 0.00000;10.15870;-3.57490;,
 1.51820;11.83560;-3.07470;,
 1.89040;14.54920;1.79900;,
 2.36150;14.28890;0.06090;,
 2.07300;14.42200;0.06090;,
 1.67470;14.49860;1.63400;,
 0.00050;14.34310;2.19930;,
 0.00050;14.38430;1.86270;,
 -2.36150;14.28900;0.05970;,
 -1.91450;14.54880;1.79800;,
 -1.69880;14.49820;1.63310;,
 -2.07310;14.42210;0.05970;,
 -1.71890;11.84420;-3.11990;,
 -1.51820;11.83560;-3.07470;,
 2.36150;14.28890;0.06090;,
 3.10900;13.98060;-2.11550;,
 2.87470;14.12670;-2.06630;,
 2.07300;14.42200;0.06090;,
 -3.10900;13.98060;-2.11550;,
 -2.36150;14.28900;0.05970;,
 -2.07310;14.42210;0.05970;,
 -2.87470;14.12670;-2.06630;,
 0.00000;10.20220;-3.52350;,
 1.17840;11.76090;-2.52550;,
 1.78520;14.05370;0.10280;,
 1.53170;13.89730;1.87630;,
 0.00000;13.42510;2.12940;,
 -1.55630;13.89730;1.87630;,
 -1.78520;14.05370;0.10280;,
 -1.17840;11.76090;-2.52550;,
 1.86700;13.68750;-1.46100;,
 1.78520;14.05370;0.10280;,
 -1.78520;14.05370;0.10280;,
 -1.86700;13.68750;-1.46100;;
 
 190;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;9,10,11,12;,
 4;10,13,14,11;,
 4;12,11,15,16;,
 4;11,14,17,15;,
 4;16,15,18,19;,
 4;15,17,20,18;,
 4;19,18,21,22;,
 4;18,20,23,21;,
 4;24,23,20,17;,
 4;13,24,17,14;,
 4;19,22,25,16;,
 4;16,25,9,12;,
 4;7,6,10,9;,
 4;6,8,13,10;,
 4;5,24,13,8;,
 4;4,23,24,5;,
 4;21,23,4,1;,
 4;22,21,1,0;,
 4;25,22,0,3;,
 4;9,25,3,7;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,30,33;,
 4;33,36,37,34;,
 4;32,38,36,33;,
 4;28,39,40,29;,
 4;32,31,26,29;,
 4;29,40,38,32;,
 4;28,27,41,42;,
 4;42,43,39,28;,
 4;34,37,44,45;,
 4;46,35,34,45;,
 4;47,48,49,50;,
 4;51,52,53,54;,
 4;55,56,57,58;,
 3;59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,62,65;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;79,80,81,76;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;75,78,77,72;,
 4;69,62,71,66;,
 4;57,60,59,58;,
 4;50,53,52,47;,
 4;89,74,73,86;,
 4;94,68,67,95;,
 4;96,97,68,94;,
 3;56,98,99;,
 3;98,100,99;,
 3;100,101,99;,
 4;102,49,48,103;,
 3;104,101,105;,
 3;101,100,105;,
 3;100,106,105;,
 4;107,108,59,61;,
 4;109,110,111,112;,
 4;54,113,114,51;,
 4;103,115,116,102;,
 4;117,118,119,120;,
 4;121,122,56,99;,
 4;57,56,122,123;,
 4;123,124,60,57;,
 4;125,60,124,126;,
 4;126,127,128,125;,
 4;70,129,130,131;,
 4;132,71,70,131;,
 4;66,71,132,133;,
 4;134,67,66,133;,
 4;95,67,134,135;,
 4;135,136,137,95;,
 4;99,138,139,121;,
 4;129,70,84,83;,
 4;70,65,85,84;,
 4;65,64,82,85;,
 4;125,128,110,109;,
 4;140,141,112,111;,
 4;141,125,109,112;,
 4;95,137,91,90;,
 4;96,94,93,92;,
 4;94,95,90,93;,
 4;138,99,119,118;,
 4;99,101,120,119;,
 4;101,104,117,120;,
 4;135,134,74,89;,
 4;75,74,134,133;,
 4;133,132,78,75;,
 4;79,78,132,131;,
 4;130,80,79,131;,
 4;51,114,127,126;,
 4;124,52,51,126;,
 4;47,52,124,123;,
 4;122,48,47,123;,
 4;103,48,122,121;,
 4;139,115,103,121;,
 4;89,88,136,135;,
 4;106,100,98,55;,
 3;142,108,140;,
 3;108,107,140;,
 3;107,141,140;,
 3;98,56,55;,
 3;125,141,60;,
 3;141,107,60;,
 3;107,61,60;,
 4;50,49,143,144;,
 4;54,53,145,146;,
 4;73,72,147,148;,
 4;77,76,149,150;,
 4;76,81,151,149;,
 4;87,86,152,153;,
 4;72,77,150,147;,
 4;53,50,144,145;,
 4;86,73,148,152;,
 4;49,102,154,143;,
 4;113,54,146,155;,
 4;102,116,156,154;,
 4;157,158,159,160;,
 4;161,162,163,164;,
 4;165,166,167,168;,
 4;169,170,171,172;,
 4;170,173,174,171;,
 4;175,176,177,178;,
 4;166,169,172,167;,
 4;162,157,160,163;,
 4;176,165,168,177;,
 4;158,179,180,159;,
 4;181,161,164,182;,
 4;179,183,184,180;,
 4;144,143,158,157;,
 4;185,186,160,159;,
 4;146,145,162,161;,
 4;187,188,164,163;,
 4;148,147,166,165;,
 4;189,190,168,167;,
 4;150,149,170,169;,
 4;191,192,172,171;,
 4;149,151,173,170;,
 4;193,191,171,174;,
 4;153,152,176,175;,
 4;194,195,178,177;,
 4;147,150,169,166;,
 4;192,189,167,172;,
 4;145,144,157,162;,
 4;186,187,163,160;,
 4;152,148,165,176;,
 4;190,194,177,168;,
 4;143,154,179,158;,
 4;196,185,159,180;,
 4;155,146,161,181;,
 4;188,197,182,164;,
 4;154,156,183,179;,
 4;198,196,180,184;,
 4;199,200,201,202;,
 4;203,204,205,206;,
 4;207,203,206,208;,
 4;209,210,211,212;,
 4;210,207,208,211;,
 4;200,213,214,201;,
 4;215,216,217,218;,
 4;219,220,221,222;,
 4;216,199,202,217;,
 4;213,219,222,214;,
 4;55,58,200,199;,
 4;223,224,202,201;,
 4;68,97,204,203;,
 4;225,226,206,205;,
 4;69,68,203,207;,
 4;226,227,208,206;,
 4;63,62,210,209;,
 4;228,229,212,211;,
 4;62,69,207,210;,
 4;227,228,211,208;,
 4;58,59,213,200;,
 4;230,223,201,214;,
 4;105,106,216,215;,
 4;231,232,218,217;,
 4;108,142,220,219;,
 4;233,234,222,221;,
 4;106,55,199,216;,
 4;224,231,217,202;,
 4;59,108,219,213;,
 4;234,230,214,222;;
 
 MeshMaterialList {
  23;
  190;
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  22,
  21,
  21,
  21,
  21,
  21,
  21,
  21,
  21,
  21,
  21,
  21,
  21,
  16,
  16,
  16,
  16,
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
  16,
  16,
  1,
  1,
  1,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  1,
  1,
  1,
  1,
  1,
  1,
  16,
  1,
  1,
  1,
  16,
  16,
  16,
  1,
  1,
  1,
  16,
  16,
  16,
  1,
  1,
  1,
  1,
  1,
  16,
  16,
  16,
  16,
  16,
  16,
  1,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  1,
  1,
  1,
  1,
  1,
  16,
  1,
  16,
  16,
  16,
  16,
  16,
  1,
  1,
  1,
  1,
  1,
  16,
  1,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
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
  16,
  16,
  1,
  1,
  16,
  16,
  16,
  16,
  16,
  16,
  18,
  1,
  1,
  1,
  1,
  18,
  16,
  16,
  18,
  18,
  16,
  16,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16;;
  Material {
   0.800000;0.320000;0.000000;1.000000;;
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
    "data/TEXTURE/hukuback.png";
   }
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
   0.800000;0.649412;0.542745;1.000000;;
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
    "data/TEXTURE/hukufront.png";
   }
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.401569;0.401569;0.401569;1.000000;;
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
   0.800000;0.721569;0.658824;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/skin.png";
   }
  }
  Material {
   0.800000;0.648000;0.544000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  249;
  0.690595;-0.222857;-0.688050;,
  0.512968;-0.414297;-0.751812;,
  -0.734276;0.114622;-0.669104;,
  0.777329;0.105353;-0.620210;,
  0.563884;0.071475;-0.822755;,
  -0.777329;0.105353;-0.620210;,
  0.762438;0.389419;-0.516760;,
  0.591494;0.519711;-0.616470;,
  -0.762438;0.389419;-0.516760;,
  0.263511;0.611823;0.745811;,
  0.000000;0.634240;0.773137;,
  -0.263511;0.611823;0.745811;,
  0.679197;0.133577;0.721698;,
  0.000000;0.128541;0.991704;,
  -0.679197;0.133577;0.721698;,
  0.615061;0.104694;0.781498;,
  0.000000;0.068857;0.997626;,
  -0.615061;0.104694;0.781498;,
  0.330130;0.942183;0.057493;,
  0.000000;0.998143;0.060908;,
  -0.330130;0.942183;0.057493;,
  -0.991316;0.130354;-0.017343;,
  -0.121471;-0.861540;0.492944;,
  0.000000;-0.867967;0.496622;,
  0.121471;-0.861540;0.492944;,
  0.991316;0.130354;-0.017343;,
  0.000000;0.115674;-0.993287;,
  0.000000;0.698442;-0.715667;,
  -0.000107;0.969940;0.243346;,
  0.000000;0.084669;0.996409;,
  -0.094558;0.084290;0.991945;,
  -0.096903;0.134268;0.986196;,
  -0.128185;0.692680;-0.709763;,
  0.022568;0.115644;-0.993034;,
  0.094558;0.084290;0.991945;,
  0.092305;0.965839;0.242147;,
  0.128185;0.692680;-0.709763;,
  -0.022568;0.115644;-0.993034;,
  0.139843;0.979912;-0.142186;,
  -0.000058;0.989648;-0.143517;,
  -0.139966;0.979918;-0.142024;,
  0.030051;0.310461;-0.950111;,
  0.000000;0.310601;-0.950540;,
  -0.030051;0.310461;-0.950111;,
  -0.095761;0.109314;0.989384;,
  0.000072;0.109893;0.993943;,
  0.095904;0.109460;0.989354;,
  -0.512968;-0.414297;-0.751812;,
  -0.563884;0.071475;-0.822755;,
  -0.591494;0.519711;-0.616470;,
  -0.987754;0.156009;0.001659;,
  -0.993682;0.106714;-0.034748;,
  -0.974265;0.102937;0.200528;,
  0.987754;0.156009;0.001659;,
  0.993682;0.106714;-0.034748;,
  0.974265;0.102937;0.200528;,
  0.000000;-0.854817;-0.518930;,
  -0.364077;-0.796150;-0.483315;,
  0.364077;-0.796150;-0.483315;,
  0.097189;0.134559;0.986128;,
  0.000144;0.135051;0.990839;,
  -0.092517;0.965739;0.242463;,
  0.000000;-0.203572;-0.979060;,
  0.419979;-0.179213;-0.889663;,
  0.361671;0.115161;-0.925166;,
  0.000000;0.125671;-0.992072;,
  -0.830117;-0.122872;-0.543883;,
  -0.419979;-0.179213;-0.889663;,
  -0.361671;0.115161;-0.925166;,
  -0.800371;0.126495;-0.586008;,
  0.036754;0.367340;-0.929360;,
  0.387669;0.138894;-0.911274;,
  0.000000;0.022923;-0.999737;,
  0.000000;-0.046768;-0.998906;,
  -0.036754;0.367340;-0.929360;,
  -0.326440;0.246163;-0.912601;,
  -0.745466;-0.185207;-0.640295;,
  -0.113276;0.899687;-0.421583;,
  0.124115;0.158175;0.979580;,
  0.018971;0.977407;-0.210513;,
  0.000637;0.176826;0.984242;,
  -0.041543;0.998214;0.042940;,
  -0.064985;0.993887;-0.089255;,
  -0.138551;0.987713;-0.072302;,
  -0.320727;0.941277;0.105510;,
  0.000097;0.160012;0.987115;,
  0.163426;0.096053;0.981869;,
  -0.245300;0.045815;0.968364;,
  -0.163301;0.095912;0.981903;,
  0.000000;0.278411;0.960462;,
  0.412773;0.260179;0.872883;,
  0.426574;-0.059204;0.902513;,
  0.000000;0.003768;0.999993;,
  -0.798562;0.210890;0.563758;,
  -0.412773;0.260179;0.872883;,
  -0.426574;-0.059204;0.902513;,
  -0.831732;-0.119243;0.542220;,
  -0.992865;-0.114940;-0.031738;,
  -0.986533;0.162352;0.019891;,
  -0.797507;0.601011;-0.052618;,
  -0.967447;0.242429;-0.072623;,
  -0.687495;0.169125;0.706220;,
  -0.707030;0.436185;0.556643;,
  0.798562;0.210890;0.563758;,
  0.986533;0.162352;0.019891;,
  0.992865;-0.114940;-0.031738;,
  0.831732;-0.119243;0.542220;,
  0.687495;0.169125;0.706220;,
  0.967447;0.242429;-0.072623;,
  0.797507;0.601011;-0.052618;,
  0.800542;0.548489;0.241436;,
  0.178134;0.100127;0.978899;,
  0.245330;0.045790;0.968358;,
  0.297606;0.953829;-0.040499;,
  0.664317;-0.121816;-0.737457;,
  0.480858;0.059935;-0.874747;,
  0.800371;0.126495;-0.586008;,
  0.830117;-0.122872;-0.543883;,
  -0.700992;-0.091791;-0.707237;,
  -0.675125;0.458888;-0.577606;,
  0.700992;-0.091791;-0.707237;,
  0.675125;0.458888;-0.577606;,
  0.855294;-0.193095;-0.480819;,
  0.617133;-0.227208;-0.753342;,
  0.000000;-0.137514;-0.990500;,
  -0.296756;-0.178573;-0.938109;,
  -0.855294;-0.193095;-0.480819;,
  -0.950767;-0.303934;-0.060540;,
  -0.791780;-0.603940;-0.091328;,
  -0.755107;-0.248324;0.606752;,
  -0.309984;-0.079400;0.947420;,
  0.000000;-0.011327;0.999936;,
  0.309984;-0.079400;0.947420;,
  0.755107;-0.248324;0.606752;,
  0.950767;-0.303934;-0.060540;,
  0.791780;-0.603940;-0.091328;,
  0.308830;0.194982;-0.930917;,
  0.059411;0.818410;-0.571556;,
  0.004338;0.782014;-0.623246;,
  -0.070606;0.889066;-0.452302;,
  0.324391;0.317593;-0.891013;,
  -0.026654;0.548998;-0.835398;,
  0.354561;-0.012628;-0.934948;,
  0.000000;-0.013672;-0.999907;,
  -0.354561;-0.012628;-0.934948;,
  -0.828026;0.003451;-0.560680;,
  0.000000;0.071630;0.997431;,
  0.336139;0.088688;0.937627;,
  -0.731601;0.081797;0.676808;,
  -0.336139;0.088688;0.937627;,
  -0.993360;0.034315;0.109815;,
  0.731601;0.081797;0.676808;,
  0.993360;0.034315;0.109815;,
  0.828026;0.003451;-0.560680;,
  0.083594;-0.971557;-0.221562;,
  0.000000;-0.965806;-0.259264;,
  -0.083594;-0.971557;-0.221562;,
  -0.143630;-0.984347;-0.102134;,
  0.000000;-0.965431;0.260659;,
  0.063318;-0.961719;0.266622;,
  -0.129280;-0.978291;0.161968;,
  -0.063318;-0.961719;0.266622;,
  -0.172156;-0.984968;0.014172;,
  0.129280;-0.978291;0.161968;,
  0.172156;-0.984968;0.014172;,
  0.143630;-0.984347;-0.102134;,
  0.358357;-0.151104;-0.921275;,
  0.000000;-0.159537;-0.987192;,
  0.362615;0.000000;-0.931939;,
  0.000000;0.000000;-1.000000;,
  -0.358357;-0.151104;-0.921275;,
  -0.835859;-0.152768;-0.527259;,
  -0.362615;0.000000;-0.931939;,
  -0.847304;0.000000;-0.531109;,
  0.000000;-0.155994;0.987758;,
  0.290267;-0.145066;0.945886;,
  0.000000;0.000000;1.000000;,
  0.295044;0.000000;0.955484;,
  -0.682198;-0.147402;0.716156;,
  -0.290267;-0.145066;0.945886;,
  -0.692816;0.000000;0.721114;,
  -0.295044;0.000000;0.955484;,
  -0.977866;-0.144596;0.151230;,
  -0.988144;0.000000;0.153528;,
  0.682198;-0.147402;0.716156;,
  0.977866;-0.144596;0.151230;,
  0.692816;0.000000;0.721114;,
  0.988144;0.000000;0.153528;,
  0.835859;-0.152768;-0.527259;,
  0.847304;0.000000;-0.531109;,
  -0.642523;0.613829;-0.458671;,
  -0.598313;0.674819;-0.432019;,
  -0.901665;0.393469;-0.179394;,
  -0.800242;0.558589;-0.218151;,
  -0.000593;-0.310849;-0.950459;,
  0.902669;0.396923;-0.166257;,
  0.800864;0.560257;-0.211494;,
  0.642523;0.613829;-0.458671;,
  -0.681812;0.631626;-0.369026;,
  0.681897;0.631516;-0.369059;,
  0.025492;0.294696;-0.955251;,
  0.000000;0.128213;-0.991747;,
  -0.226532;0.351772;-0.908262;,
  -0.347778;0.508953;-0.787412;,
  0.037330;0.998834;-0.030604;,
  0.328384;0.944532;-0.004711;,
  -0.000636;0.999995;-0.003029;,
  -0.037715;0.998765;-0.032339;,
  -0.328199;0.944590;-0.005949;,
  -0.025492;0.294696;-0.955251;,
  0.347778;0.508953;-0.787412;,
  0.479480;0.876191;0.048867;,
  -0.479538;0.876159;0.048871;,
  -0.123235;0.158179;0.979690;,
  -0.178086;0.100163;0.978904;,
  0.041488;0.998212;0.043031;,
  0.320700;0.941281;0.105557;,
  0.138581;0.944708;-0.297189;,
  -0.024987;0.930828;-0.364603;,
  -0.030780;0.092344;-0.995251;,
  -0.851280;-0.045909;-0.522700;,
  -0.704496;-0.615418;0.353477;,
  0.704496;-0.615418;0.353477;,
  -0.503798;-0.752096;0.424899;,
  -0.554157;-0.585187;-0.592002;,
  -0.644009;0.047768;-0.763525;,
  0.503798;-0.752096;0.424899;,
  0.286716;0.074434;0.955120;,
  0.554157;-0.585187;-0.592002;,
  -0.079222;0.450577;-0.889216;,
  -0.519793;0.618693;-0.589096;,
  0.079222;0.450577;-0.889216;,
  0.519858;0.618616;-0.589120;,
  0.830846;-0.556341;0.013394;,
  0.844375;-0.343060;-0.411511;,
  0.969715;-0.147183;0.194912;,
  0.895778;-0.378831;0.232527;,
  0.189099;0.105947;0.976226;,
  0.001082;0.108176;0.994131;,
  -0.089912;-0.309134;-0.946759;,
  -0.897247;-0.379345;0.225931;,
  -0.972049;-0.148348;0.181969;,
  -0.186974;0.106545;0.976570;,
  0.088730;-0.310079;-0.946561;,
  -0.844375;-0.343060;-0.411511;,
  -0.830846;-0.556341;0.013394;,
  0.598313;0.674819;-0.432019;,
  0.703285;-0.619885;0.348041;,
  -0.703394;-0.619739;0.348081;;
  190;
  4;0,1,4,3;,
  4;47,2,5,48;,
  4;3,4,7,6;,
  4;48,5,8,49;,
  4;18,19,10,9;,
  4;19,20,11,10;,
  4;9,10,13,12;,
  4;10,11,14,13;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;24,23,23,24;,
  4;23,22,22,23;,
  4;21,50,17,14;,
  4;51,21,14,52;,
  4;15,53,25,12;,
  4;12,25,54,55;,
  4;6,7,19,18;,
  4;49,8,20,19;,
  4;5,21,51,8;,
  4;2,50,21,5;,
  4;56,57,57,47;,
  4;58,56,1,0;,
  4;25,53,0,3;,
  4;54,25,3,6;,
  4;36,41,42,27;,
  4;35,38,39,28;,
  4;45,46,59,60;,
  4;60,31,44,45;,
  4;39,40,61,28;,
  4;42,43,32,27;,
  4;39,38,36,27;,
  4;27,32,40,39;,
  4;42,41,37,26;,
  4;26,33,43,42;,
  4;45,44,30,29;,
  4;34,46,45,29;,
  4;62,63,64,65;,
  4;66,67,68,69;,
  4;70,71,72,73;,
  3;74,75,141;,
  4;81,82,83,84;,
  4;85,86,78,80;,
  4;87,88,213,214;,
  4;89,90,91,92;,
  4;93,94,95,96;,
  4;96,97,98,93;,
  4;99,100,101,102;,
  4;103,104,105,106;,
  4;107,108,109,110;,
  4;92,95,94,89;,
  4;80,213,88,85;,
  4;72,75,74,73;,
  4;65,68,67,62;,
  4;106,91,90,103;,
  4;111,78,86,112;,
  4;113,79,215,216;,
  3;71,140,114;,
  3;140,136,114;,
  3;136,115,114;,
  4;116,64,63,117;,
  3;113,217,79;,
  3;217,218,79;,
  3;218,137,79;,
  4;138,139,74,141;,
  4;118,100,99,119;,
  4;69,98,97,66;,
  4;117,105,104,116;,
  4;109,108,120,121;,
  4;122,123,71,114;,
  4;72,71,219,124;,
  4;124,125,75,72;,
  4;76,75,220,126;,
  4;126,127,128,76;,
  4;221,128,127,129;,
  4;130,88,87,129;,
  4;85,88,130,131;,
  4;132,86,85,131;,
  4;112,86,132,133;,
  4;133,134,135,222;,
  4;114,135,134,122;,
  4;128,221,223,223;,
  4;87,214,102,101;,
  4;84,83,99,102;,
  4;76,128,224,118;,
  4;83,77,119,99;,
  4;225,76,118,119;,
  4;222,135,226,226;,
  4;113,216,110,109;,
  4;111,112,107,227;,
  4;135,114,120,228;,
  4;114,115,121,120;,
  4;217,113,109,121;,
  4;133,132,91,106;,
  4;92,91,132,131;,
  4;131,130,95,92;,
  4;96,95,130,129;,
  4;127,97,96,129;,
  4;66,97,127,126;,
  4;125,67,66,126;,
  4;62,67,125,124;,
  4;123,63,62,124;,
  4;117,63,123,122;,
  4;134,105,117,122;,
  4;106,105,134,133;,
  4;137,136,140,70;,
  3;82,139,83;,
  3;139,138,83;,
  3;138,77,83;,
  3;140,71,70;,
  3;76,225,75;,
  3;77,138,75;,
  3;138,141,75;,
  4;65,64,142,143;,
  4;69,68,144,145;,
  4;90,89,146,147;,
  4;94,93,148,149;,
  4;93,98,150,148;,
  4;104,103,151,152;,
  4;89,94,149,146;,
  4;68,65,143,144;,
  4;103,90,147,151;,
  4;64,116,153,142;,
  4;98,69,145,150;,
  4;116,104,152,153;,
  4;167,166,168,169;,
  4;171,170,172,173;,
  4;175,174,176,177;,
  4;179,178,180,181;,
  4;178,182,183,180;,
  4;185,184,186,187;,
  4;174,179,181,176;,
  4;170,167,169,172;,
  4;184,175,177,186;,
  4;166,188,189,168;,
  4;182,171,173,183;,
  4;188,185,187,189;,
  4;143,142,166,167;,
  4;154,155,155,154;,
  4;145,144,170,171;,
  4;156,157,157,156;,
  4;147,146,174,175;,
  4;158,159,159,158;,
  4;149,148,178,179;,
  4;160,161,161,160;,
  4;148,150,182,178;,
  4;162,160,160,162;,
  4;152,151,184,185;,
  4;163,164,164,163;,
  4;146,149,179,174;,
  4;161,158,158,161;,
  4;144,143,167,170;,
  4;155,156,156,155;,
  4;151,147,175,184;,
  4;159,163,163,159;,
  4;142,153,188,166;,
  4;165,154,154,165;,
  4;150,145,171,182;,
  4;157,162,162,157;,
  4;153,152,185,188;,
  4;164,165,165,164;,
  4;200,201,202,203;,
  4;204,205,205,204;,
  4;206,204,204,206;,
  4;208,207,207,208;,
  4;207,206,206,207;,
  4;201,209,210,202;,
  4;205,211,211,205;,
  4;212,208,208,212;,
  4;229,200,203,230;,
  4;209,231,232,210;,
  4;233,234,234,233;,
  4;191,190,203,202;,
  4;235,236,236,235;,
  4;193,192,192,193;,
  4;80,78,237,238;,
  4;239,194,194,239;,
  4;240,241,241,240;,
  4;195,196,196,195;,
  4;213,80,238,242;,
  4;194,243,243,194;,
  4;244,245,245,244;,
  4;197,246,246,210;,
  4;236,247,247,236;,
  4;198,193,193,230;,
  4;248,240,240,248;,
  4;196,199,232,196;,
  4;247,233,233,247;,
  4;190,198,230,203;,
  4;245,248,248,245;,
  4;199,197,210,232;;
 }
 MeshTextureCoords {
  235;
  0.693531;0.161300;,
  0.500000;0.238752;,
  0.500000;-0.229393;,
  0.693531;-0.229393;,
  0.306469;0.161300;,
  0.306469;-0.229393;,
  0.500000;-0.672006;,
  0.659765;-0.606993;,
  0.340235;-0.606993;,
  0.693531;-0.655480;,
  0.500000;-0.731266;,
  0.500000;-0.606993;,
  0.693531;-0.606993;,
  0.306469;-0.655480;,
  0.306469;-0.606993;,
  0.500000;-0.229393;,
  0.693531;-0.229393;,
  0.306469;-0.229393;,
  0.500000;0.171716;,
  0.693531;0.148206;,
  0.306469;0.148206;,
  0.500000;0.351836;,
  0.900672;0.279958;,
  0.099328;0.279958;,
  0.244670;-0.229393;,
  0.755330;-0.229393;,
  1.046196;0.383595;,
  1.046196;0.945600;,
  0.494289;0.865013;,
  0.494289;0.472772;,
  1.041851;0.276463;,
  1.046196;0.266563;,
  0.494289;0.103743;,
  0.494289;0.303960;,
  0.494289;0.849300;,
  1.050203;0.845789;,
  -0.057617;0.276463;,
  -0.061625;0.845789;,
  -0.057617;0.266563;,
  -0.057617;0.945600;,
  -0.057617;0.383595;,
  1.046196;1.176131;,
  0.494289;1.176131;,
  -0.057617;1.176131;,
  -0.057617;1.176131;,
  0.494289;1.176131;,
  1.046196;1.176131;,
  0.505778;-0.516398;,
  0.752445;-0.516398;,
  0.715829;-0.317488;,
  0.505778;-0.317488;,
  0.194701;-0.516398;,
  0.259112;-0.516398;,
  0.295728;-0.317488;,
  0.197105;-0.317488;,
  0.598308;-0.944844;,
  0.770715;-0.841726;,
  0.505778;-0.751465;,
  0.505778;-0.763634;,
  0.413249;-0.944844;,
  0.240842;-0.841726;,
  0.126389;-1.087798;,
  0.350206;0.032636;,
  0.344324;0.021640;,
  0.107579;0.037409;,
  0.121320;0.036193;,
  0.500000;0.229910;,
  0.729772;0.228511;,
  0.647994;0.032636;,
  0.500000;0.093801;,
  0.127297;0.229278;,
  0.270228;0.228511;,
  0.500000;0.701879;,
  0.689852;0.701879;,
  0.712388;0.537310;,
  0.500000;0.537310;,
  0.214395;0.701879;,
  0.310148;0.701879;,
  0.287612;0.537310;,
  0.212090;0.537310;,
  0.179897;0.537310;,
  0.190052;0.701879;,
  0.046529;0.070003;,
  -0.000847;0.217945;,
  0.045643;0.193507;,
  0.067849;0.083135;,
  0.785605;0.701879;,
  0.809948;0.701879;,
  0.820103;0.537310;,
  0.787910;0.537310;,
  0.954357;0.193507;,
  1.000847;0.217945;,
  0.953471;0.070003;,
  0.932151;0.083135;,
  0.878680;0.036193;,
  0.872703;0.229278;,
  0.892421;0.037409;,
  0.655676;0.021640;,
  0.885168;-1.087798;,
  0.902579;-0.879838;,
  0.893020;-1.091639;,
  0.914595;-1.102193;,
  0.814452;-0.317488;,
  0.816856;-0.516398;,
  0.961535;-1.120615;,
  0.686581;-1.139675;,
  0.698290;-1.108557;,
  0.118537;-1.091639;,
  0.313267;-1.108557;,
  0.006370;-0.933856;,
  -0.075904;-0.902407;,
  -0.020882;-1.081221;,
  0.021461;-1.082495;,
  0.145806;-0.317488;,
  0.134011;-0.516398;,
  0.877546;-0.516398;,
  0.865751;-0.317488;,
  1.032439;-1.081221;,
  1.087461;-0.902407;,
  1.005187;-0.933856;,
  0.990096;-1.082495;,
  0.855393;-0.731063;,
  0.770715;-0.731063;,
  0.505778;-0.731063;,
  0.240842;-0.731063;,
  0.108977;-0.879838;,
  0.156164;-0.731063;,
  0.093359;-0.731063;,
  0.059012;-0.791378;,
  0.115320;0.309805;,
  0.144894;0.359707;,
  0.181784;0.359707;,
  0.271882;0.359707;,
  0.500000;0.359707;,
  0.728118;0.359707;,
  0.818216;0.359707;,
  0.855106;0.359707;,
  0.884680;0.309805;,
  0.952545;-0.791378;,
  0.918198;-0.731063;,
  0.050021;-1.120615;,
  0.096962;-1.102193;,
  0.324976;-1.139675;,
  0.731915;-0.171644;,
  0.505778;-0.171644;,
  0.279642;-0.171644;,
  0.133051;-0.171644;,
  0.500000;0.822318;,
  0.668729;0.822318;,
  0.218002;0.826811;,
  0.331271;0.822318;,
  0.152335;0.822543;,
  0.781998;0.826811;,
  0.847665;0.822543;,
  0.878506;-0.171644;,
  0.102001;-0.171644;,
  0.909556;-0.171644;,
  0.505778;-0.107887;,
  0.731719;-0.107887;,
  0.731719;0.009294;,
  0.505778;0.009294;,
  0.149205;-0.107887;,
  0.279837;-0.107887;,
  0.279837;0.009294;,
  0.149205;0.009294;,
  0.671385;0.875103;,
  0.500000;0.875103;,
  0.500000;0.972053;,
  0.671385;0.972053;,
  0.328615;0.875103;,
  0.227667;0.878906;,
  0.227667;0.975863;,
  0.328615;0.972053;,
  0.169148;0.875293;,
  0.169148;0.972243;,
  0.830852;0.875293;,
  0.772333;0.878906;,
  0.772333;0.975863;,
  0.830852;0.972243;,
  0.862352;-0.107887;,
  0.862352;0.009294;,
  0.121528;-0.107887;,
  0.121528;0.009294;,
  0.890029;-0.107887;,
  0.890029;0.009294;,
  0.720851;0.014180;,
  0.505778;0.014180;,
  0.290706;0.014180;,
  0.176822;0.014180;,
  0.500000;0.976060;,
  0.664998;0.976060;,
  0.246998;0.980553;,
  0.335002;0.976060;,
  0.195979;0.976285;,
  0.753002;0.980553;,
  0.804021;0.976285;,
  0.834735;0.014180;,
  0.152689;0.014180;,
  0.858868;0.014180;,
  0.651843;-0.967838;,
  0.505778;-0.800581;,
  0.505778;-0.824612;,
  0.634788;-0.967107;,
  0.638314;-0.026364;,
  0.672783;-0.008064;,
  0.651674;-0.017421;,
  0.622532;-0.022807;,
  0.500037;-0.011874;,
  0.500037;-0.014771;,
  0.327217;-0.008071;,
  0.359923;-0.026336;,
  0.375705;-0.022778;,
  0.348319;-0.017428;,
  0.359714;-0.967838;,
  0.376769;-0.967107;,
  0.706448;-1.175578;,
  0.769967;-1.149380;,
  0.750057;-1.161795;,
  0.681932;-1.186888;,
  0.241590;-1.149380;,
  0.305109;-1.175586;,
  0.329616;-1.186896;,
  0.261500;-1.161795;,
  0.505778;-0.828309;,
  0.605913;-0.960760;,
  0.630617;0.008472;,
  0.612069;0.019468;,
  0.500000;0.052665;,
  0.386131;0.019468;,
  0.369383;0.008472;,
  0.405643;-0.960760;,
  0.664427;-1.124473;,
  0.657476;-1.155591;,
  0.354080;-1.155591;,
  0.347129;-1.124473;;
 }
}