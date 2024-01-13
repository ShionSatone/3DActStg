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
 40;
 11.76499;-48.31209;10.02159;,
 16.61387;-52.91659;-9.33178;,
 6.49811;-5.75027;-0.25025;,
 4.42218;-6.46046;0.47356;,
 11.76294;-47.01525;-20.46678;,
 4.41751;-3.51227;-4.47186;,
 0.07047;-44.54543;-25.07911;,
 0.00388;-2.45429;-6.45055;,
 -11.61428;-46.95397;-20.46680;,
 -4.54168;-3.48878;-4.47186;,
 -16.44658;-52.82993;-9.33178;,
 -6.61521;-5.71590;-0.25025;,
 -11.61220;-48.25082;10.02159;,
 -4.53701;-6.43698;0.47356;,
 0.03869;-24.45579;-3.85714;,
 0.01186;-7.49530;2.45225;,
 -4.53701;-6.43698;0.47356;,
 0.01186;-7.49530;2.45225;,
 -0.00731;4.61890;-0.38598;,
 4.42218;-6.46046;0.47356;,
 6.49811;-5.75027;-0.25025;,
 4.41751;-3.51227;-4.47186;,
 0.00388;-2.45429;-6.45055;,
 -4.54168;-3.48878;-4.47186;,
 -6.61521;-5.71590;-0.25025;,
 -11.53551;-49.20527;18.55536;,
 0.07489;-47.33862;23.22753;,
 0.00418;-2.64068;4.77922;,
 -4.54174;-3.44789;2.76188;,
 11.69131;-49.26614;18.55536;,
 4.41745;-3.47137;2.76188;,
 16.50904;-53.85868;7.27584;,
 6.49629;-4.60079;-0.00629;,
 14.28134;-50.55889;-12.18921;,
 4.42199;-6.34296;-4.31038;,
 -16.33877;-53.77258;7.27584;,
 -6.61703;-4.56642;-0.00629;,
 0.03745;-23.67204;2.81714;,
 -14.12149;-50.48447;-12.18923;,
 -0.00829;5.23630;-1.45883;;
 
 45;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 3;1,0,14;,
 3;4,1,14;,
 3;6,4,14;,
 3;8,6,14;,
 3;10,8,14;,
 3;3,15,0;,
 3;15,13,0;,
 3;14,0,10;,
 3;13,12,0;,
 3;12,10,0;,
 3;16,17,18;,
 3;17,19,18;,
 3;19,20,18;,
 3;20,21,18;,
 3;21,22,18;,
 3;22,23,18;,
 3;23,24,18;,
 3;24,16,18;,
 4;25,26,27,28;,
 4;26,29,30,27;,
 4;29,31,32,30;,
 4;31,33,34,32;,
 4;35,25,28,36;,
 3;26,25,37;,
 3;29,26,37;,
 3;31,29,37;,
 3;33,31,37;,
 3;35,38,37;,
 3;25,35,37;,
 3;28,27,39;,
 3;27,30,39;,
 3;30,32,39;,
 3;35,36,37;,
 3;36,39,37;,
 3;37,39,32;,
 3;37,32,33;,
 3;32,34,33;,
 3;37,38,35;,
 3;36,28,39;;
 
 MeshMaterialList {
  1;
  45;
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\witch.jpg";
   }
  }
 }
 MeshNormals {
  58;
  -0.419767;0.155325;0.894243;,
  0.200898;0.171178;0.964540;,
  0.961527;0.184591;0.203451;,
  0.726296;0.337504;-0.598820;,
  0.003778;0.407103;-0.913374;,
  -0.724090;0.335261;-0.602738;,
  -0.962716;0.179460;0.202414;,
  -0.367135;0.153627;0.917393;,
  -0.009206;0.202094;0.979323;,
  0.445069;0.186179;0.875929;,
  0.944604;0.317666;0.082527;,
  0.712503;0.469429;-0.521513;,
  0.005505;0.534213;-0.845332;,
  -0.708410;0.472388;-0.524409;,
  -0.944542;0.317436;0.084111;,
  -0.763692;-0.604155;0.227531;,
  0.003191;0.208059;0.978111;,
  -0.682467;0.323084;0.655633;,
  0.003691;0.383757;0.923427;,
  0.684889;0.325286;0.652009;,
  0.969877;0.234657;0.065380;,
  0.945447;0.173226;-0.275905;,
  0.879472;-0.475537;0.019852;,
  -0.903972;0.380091;0.195870;,
  -0.650526;0.458147;0.605736;,
  0.005367;0.506956;0.861955;,
  0.654935;0.455827;0.602729;,
  0.920215;0.354199;0.166576;,
  -0.827682;0.417119;0.375440;,
  -0.116807;-0.286479;-0.950939;,
  0.301993;0.656778;0.690973;,
  -0.864290;-0.502991;-0.001871;,
  -0.868037;-0.485937;-0.101869;,
  -0.666153;-0.634638;0.391758;,
  -0.001441;-0.726216;0.687465;,
  0.665376;-0.634725;0.392937;,
  0.487119;-0.852672;0.188854;,
  0.575895;-0.180760;-0.797290;,
  -0.002550;-0.972986;0.230851;,
  0.268151;0.180620;0.946294;,
  0.682375;0.588934;-0.433037;,
  -0.675336;0.596362;-0.433906;,
  -0.266251;0.182667;0.946437;,
  -0.001314;-0.653090;-0.757279;,
  0.662586;-0.587033;-0.465158;,
  -0.663291;-0.587258;-0.463867;,
  -0.870892;-0.486007;-0.073103;,
  -0.980829;-0.184716;-0.062077;,
  -0.880353;-0.388498;0.272118;,
  0.871444;-0.484977;-0.073364;,
  -0.000384;-0.146323;-0.989237;,
  -0.000384;-0.146323;-0.989237;,
  -0.000384;-0.146323;-0.989237;,
  -0.335834;-0.025660;-0.941572;,
  -0.627841;0.098323;-0.772106;,
  -0.818934;-0.272596;0.505013;,
  -0.879472;0.475537;-0.019852;,
  -0.755556;0.559793;0.340244;;
  45;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,0,7,14;,
  3;31,32,15;,
  3;33,31,15;,
  3;34,33,15;,
  3;35,34,35;,
  3;36,35,35;,
  3;9,8,1;,
  3;8,7,1;,
  3;37,37,37;,
  3;7,0,1;,
  3;38,36,38;,
  3;7,8,16;,
  3;8,9,16;,
  3;9,39,16;,
  3;10,11,40;,
  3;11,12,40;,
  3;12,13,41;,
  3;13,14,41;,
  3;42,7,16;,
  4;17,18,25,24;,
  4;18,19,26,25;,
  4;19,20,27,26;,
  4;20,21,21,27;,
  4;23,17,24,28;,
  3;43,44,29;,
  3;45,43,29;,
  3;46,45,47;,
  3;48,46,47;,
  3;49,22,49;,
  3;44,49,49;,
  3;24,25,30;,
  3;25,26,30;,
  3;26,27,30;,
  3;50,51,29;,
  3;51,52,29;,
  3;29,52,53;,
  3;29,53,54;,
  3;55,55,48;,
  3;47,56,23;,
  3;28,24,57;;
 }
 MeshTextureCoords {
  40;
  0.833470;0.762100;,
  0.816290;0.779570;,
  0.839380;0.719660;,
  0.843490;0.720530;,
  0.819720;0.783090;,
  0.842500;0.716530;,
  0.849590;0.785490;,
  0.851420;0.714890;,
  0.881100;0.783960;,
  0.860940;0.716490;,
  0.886770;0.780520;,
  0.864630;0.719630;,
  0.871400;0.762450;,
  0.860550;0.720520;,
  0.851610;0.742170;,
  0.851990;0.721820;,
  0.463610;0.927550;,
  0.448410;0.921260;,
  0.448410;0.943600;,
  0.433220;0.927550;,
  0.426930;0.942740;,
  0.433220;0.957930;,
  0.448410;0.964230;,
  0.463610;0.957930;,
  0.469900;0.942740;,
  0.899900;0.785760;,
  0.927380;0.786720;,
  0.924890;0.721860;,
  0.915990;0.722970;,
  0.952790;0.784580;,
  0.933050;0.723020;,
  0.956620;0.781530;,
  0.936280;0.724480;,
  0.945350;0.768160;,
  0.931700;0.726550;,
  0.892930;0.782870;,
  0.912180;0.724440;,
  0.924700;0.746110;,
  0.901220;0.768850;,
  0.924270;0.713660;;
 }
}
