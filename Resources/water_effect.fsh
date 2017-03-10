uniform sampler2D u_normalMap;  
//uniform vec2 velocity;
  
#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying vec4 v_fragmentColor;
#else
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
#endif

vec3 waveNormal(vec2 p) {  
    vec3 normal = texture2D(u_normalMap, p / 2).xyz;  
    normal = -1.0 + normal * 2.0;  
    return normalize(normal);  
}  


//高光计算 参见基本光照公式
//参数说明：n法向量， l入射光向量， e观察向量
float specular(vec3 n,vec3 l,vec3 e) {    
    return pow(max(dot(reflect(e,n),l),0.0),2); 
}
  
void main() {  

    float timeFactor = 0.01;
    float offsetFactor = 0.5;
    float refractionFactor = 0.7;

    // simple UV animation
    vec3 normal = waveNormal(v_texCoord + vec2(CC_Time.y * timeFactor, 0));

    // simple calculate refraction UV offset
    vec2 p = -1 + 2 * v_texCoord; 
    vec3 eyePos = vec3(0.3, 0.3, 10);//眼睛的位置 在中心点正上方

    vec3 inVec = normalize(vec3(p, 0) - eyePos);
    vec3 refractVec = refract(inVec, normal, refractionFactor);
    vec2 v_texCoordN = v_texCoord;
    v_texCoordN += refractVec.xy * offsetFactor;
    
    vec3 light = vec3(0.2,0.1,0);    
    // bteitler: Apply specular highlight
    vec3 normalN = waveNormal(v_texCoordN );
    vec3 color = vec3(specular(normalN,light,eyePos));

    //gl_FragColor = texture2D(CC_Texture0, v_texCoordN); //这样可以看到不带高光的水面，可选
    //gl_FragColor = texture2D(u_normalMap, v_texCoordN); //这样可以只看法线图，可选
    //gl_FragColor = texture2D(CC_Texture0, lerp(v_texCoord, v_texCoordN, 0.3) + (velocity) * vec2(1,-1) * CC_Time.y )*0.9 
    //vec4(color,1) * 0.1; //加了高光效果的水面

    gl_FragColor = texture2D(CC_Texture0, lerp(v_texCoord, v_texCoordN, 0.3)) + vec4(color,1) * 0.1; //加了高光效果的水面
} 