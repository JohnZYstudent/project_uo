// Made with Amplify Shader Editor
// Available at the Unity Asset Store - http://u3d.as/y3X 
Shader "Devil_Body_Material"
{
	Properties
	{
		_Devil_body_D("Devil_body_D", 2D) = "white" {}
		_Devil_body_E("Devil_body_E", 2D) = "white" {}
		_Devil_body_layered("Devil_body_layered", 2D) = "white" {}
		_Devil_body_N("Devil_body_N", 2D) = "white" {}
		[HDR]_Body_Emission_Color("Body_Emission_Color", Color) = (0,0,0,0)
		[HDR]_Emission_Color("Emission_Color", Color) = (0,0,0,0)
		[HideInInspector] _texcoord( "", 2D ) = "white" {}
		[HideInInspector] __dirty( "", Int ) = 1
	}

	SubShader
	{
		Tags{ "RenderType" = "Opaque"  "Queue" = "Geometry+0" "IsEmissive" = "true"  }
		Cull Back
		CGPROGRAM
		#pragma target 3.0
		#pragma surface surf Standard keepalpha addshadow fullforwardshadows 
		struct Input
		{
			float2 uv_texcoord;
		};

		uniform sampler2D _Devil_body_N;
		uniform float4 _Devil_body_N_ST;
		uniform sampler2D _Devil_body_D;
		uniform float4 _Devil_body_D_ST;
		uniform float4 _Emission_Color;
		uniform sampler2D _Devil_body_E;
		uniform float4 _Devil_body_E_ST;
		uniform float4 _Body_Emission_Color;
		uniform sampler2D _Devil_body_layered;
		uniform float4 _Devil_body_layered_ST;

		void surf( Input i , inout SurfaceOutputStandard o )
		{
			float2 uv_Devil_body_N = i.uv_texcoord * _Devil_body_N_ST.xy + _Devil_body_N_ST.zw;
			o.Normal = tex2D( _Devil_body_N, uv_Devil_body_N ).rgb;
			float2 uv_Devil_body_D = i.uv_texcoord * _Devil_body_D_ST.xy + _Devil_body_D_ST.zw;
			o.Albedo = tex2D( _Devil_body_D, uv_Devil_body_D ).rgb;
			float2 uv_Devil_body_E = i.uv_texcoord * _Devil_body_E_ST.xy + _Devil_body_E_ST.zw;
			float2 uv_Devil_body_layered = i.uv_texcoord * _Devil_body_layered_ST.xy + _Devil_body_layered_ST.zw;
			o.Emission = ( ( _Emission_Color * tex2D( _Devil_body_E, uv_Devil_body_E ) ) + ( _Body_Emission_Color * ( 1.0 - tex2D( _Devil_body_layered, uv_Devil_body_layered ).b ) ) ).rgb;
			o.Alpha = 1;
		}

		ENDCG
	}
	Fallback "Diffuse"
	CustomEditor "ASEMaterialInspector"
}
/*ASEBEGIN
Version=16400
134;387;1576;907;2385.224;133.981;2.455633;True;False
Node;AmplifyShaderEditor.SamplerNode;3;-1616.3,1061.928;Float;True;Property;_Devil_body_layered;Devil_body_layered;2;0;Create;True;0;0;False;0;9d7437be8718cb0488379e0b2d75346b;9d7437be8718cb0488379e0b2d75346b;True;0;False;white;Auto;False;Object;-1;Auto;Texture2D;6;0;SAMPLER2D;;False;1;FLOAT2;0,0;False;2;FLOAT;0;False;3;FLOAT2;0,0;False;4;FLOAT2;0,0;False;5;FLOAT;1;False;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.ColorNode;13;-1223.935,281.5326;Float;False;Property;_Emission_Color;Emission_Color;5;1;[HDR];Create;True;0;0;False;0;0,0,0,0;0,0,0,0;True;0;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.ColorNode;10;-1271.062,823.9089;Float;False;Property;_Body_Emission_Color;Body_Emission_Color;4;1;[HDR];Create;True;0;0;False;0;0,0,0,0;0,0,0,0;True;0;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SamplerNode;2;-1307.32,577.3139;Float;True;Property;_Devil_body_E;Devil_body_E;1;0;Create;True;0;0;False;0;0b864b9f87451c549b7c915071788978;0b864b9f87451c549b7c915071788978;True;0;False;white;Auto;False;Object;-1;Auto;Texture2D;6;0;SAMPLER2D;;False;1;FLOAT2;0,0;False;2;FLOAT;0;False;3;FLOAT2;0,0;False;4;FLOAT2;0,0;False;5;FLOAT;1;False;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.OneMinusNode;8;-1204.943,1137.607;Float;False;1;0;FLOAT;0;False;1;FLOAT;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;11;-945.3467,974.4208;Float;False;2;2;0;COLOR;0,0,0,0;False;1;FLOAT;0;False;1;COLOR;0
Node;AmplifyShaderEditor.SimpleMultiplyOpNode;14;-947.2756,426.196;Float;False;2;2;0;COLOR;0,0,0,0;False;1;COLOR;0,0,0,0;False;1;COLOR;0
Node;AmplifyShaderEditor.SamplerNode;1;-613,-134;Float;True;Property;_Devil_body_D;Devil_body_D;0;0;Create;True;0;0;False;0;3c64218762b29f54f9ba55621a0ba376;3c64218762b29f54f9ba55621a0ba376;True;0;False;white;Auto;False;Object;-1;Auto;Texture2D;6;0;SAMPLER2D;;False;1;FLOAT2;0,0;False;2;FLOAT;0;False;3;FLOAT2;0,0;False;4;FLOAT2;0,0;False;5;FLOAT;1;False;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.SimpleAddOpNode;12;-643.494,706.3481;Float;False;2;2;0;COLOR;0,0,0,0;False;1;COLOR;0,0,0,0;False;1;COLOR;0
Node;AmplifyShaderEditor.SamplerNode;4;-613,62;Float;True;Property;_Devil_body_N;Devil_body_N;3;0;Create;True;0;0;False;0;8e86381e46514fc45971c26b54437816;8e86381e46514fc45971c26b54437816;True;0;False;white;Auto;False;Object;-1;Auto;Texture2D;6;0;SAMPLER2D;;False;1;FLOAT2;0,0;False;2;FLOAT;0;False;3;FLOAT2;0,0;False;4;FLOAT2;0,0;False;5;FLOAT;1;False;5;COLOR;0;FLOAT;1;FLOAT;2;FLOAT;3;FLOAT;4
Node;AmplifyShaderEditor.StandardSurfaceOutputNode;0;0,0;Float;False;True;2;Float;ASEMaterialInspector;0;0;Standard;Devil_Body_Material;False;False;False;False;False;False;False;False;False;False;False;False;False;False;False;False;False;False;False;False;False;Back;0;False;-1;0;False;-1;False;0;False;-1;0;False;-1;False;0;Opaque;0.5;True;True;0;False;Opaque;;Geometry;All;True;True;True;True;True;True;True;True;True;True;True;True;True;True;True;True;True;0;False;-1;False;0;False;-1;255;False;-1;255;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;-1;False;2;15;10;25;False;0.5;True;0;0;False;-1;0;False;-1;0;0;False;-1;0;False;-1;0;False;-1;0;False;-1;0;False;0;0,0,0,0;VertexOffset;True;False;Cylindrical;False;Relative;0;;-1;-1;-1;-1;0;False;0;0;False;-1;-1;0;False;-1;0;0;0;False;0.1;False;-1;0;False;-1;16;0;FLOAT3;0,0,0;False;1;FLOAT3;0,0,0;False;2;FLOAT3;0,0,0;False;3;FLOAT;0;False;4;FLOAT;0;False;5;FLOAT;0;False;6;FLOAT3;0,0,0;False;7;FLOAT3;0,0,0;False;8;FLOAT;0;False;9;FLOAT;0;False;10;FLOAT;0;False;13;FLOAT3;0,0,0;False;11;FLOAT3;0,0,0;False;12;FLOAT3;0,0,0;False;14;FLOAT4;0,0,0,0;False;15;FLOAT3;0,0,0;False;0
WireConnection;8;0;3;3
WireConnection;11;0;10;0
WireConnection;11;1;8;0
WireConnection;14;0;13;0
WireConnection;14;1;2;0
WireConnection;12;0;14;0
WireConnection;12;1;11;0
WireConnection;0;0;1;0
WireConnection;0;1;4;0
WireConnection;0;2;12;0
ASEEND*/
//CHKSM=C838593231311DBEF7E4D62318413A16A229CCF0