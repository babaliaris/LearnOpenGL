#version 330 core

in vec3 fragPos;
in vec3 normal;
in vec2 textCoord;

uniform sampler2D diffuse;
uniform sampler2D specular;

out vec4 fragColor;


struct DirectionalLight
{
    vec3 direction;

    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3  position;
    float linear;
    float quadratic;

    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3  position;
    vec3  direction;
    float linear;
    float quadratic;
    float inner_cutoff;
    float outer_cutoff;

    vec3 diffuse;
    vec3 specular;
};


uniform DirectionalLight    dLight;
uniform PointLight          pLights[50];
uniform SpotLight           sLight;

uniform vec3                camPos;    
uniform vec3                ambient;

uniform int hasDLight;
uniform int hasPLight;
uniform int hasSLight;


vec4 calculateDirectionalDiffuse();
vec4 calculateDirectionalSpecular();

vec4 calculatePointDiffuse(PointLight point);
vec4 calculatePointSpecular(PointLight point);


void main()
{
    vec4 ambient_color  = vec4(ambient, 1.0) * texture(diffuse, textCoord);
    vec4 diffuse_color  = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 specular_color = vec4(0.0, 0.0, 0.0, 1.0);

    
    if (hasDLight)
    {
        diffuse_color  += calculateDirectionalDiffuse();
        specular_color += calculateDirectionalSpecular();
    }

    if (hasPLight)
    {
        for (int i = 0; i < 50; i++)
        {
            if (pLights[i].diffuse == vec3(0.0, 0.0, 0.0))
            {
                break;
            }


            diffuse_color  += calculatePointDiffuse(pLights[i]);
            specular_color += calculatePointSpecular(pLights[i]);

        }
    }
        

    fragColor = ambient_color + diffuse_color + specular_color;
}





vec4 calculateDirectionalDiffuse()
{
    vec3 lightDir = normalize(-dLight.direction);

    float diffuseFactor = max( dot(lightDir, normal), 0.0 );

    vec4 diffuse_color = vec4(dLight.diffuse, 1.0) * texture(diffuse, textCoord) * diffuseFactor;

    return diffuse_color;
}





vec4 calculateDirectionalSpecular()
{
    vec3 lightDir     = normalize(dLight.direction);
    vec3 reflection   = normalize(reflect(lightDir, normal));
    vec3 camDirection = normalize(camPos - fragPos);

    float specular_factor = pow( max( dot(camDirection, reflection), 0.0 ), 32);

    vec4 specular_color = vec4(dLight.specular, 1.0) * texture(specular, textCoord) * specular_factor;

    return specular_color;
}




vec4 calculatePointDiffuse(PointLight point)
{
    vec3 lightDir = normalize(point.position - fragPos);

    float diffuseFactor = max( dot(lightDir, normal), 0.0 );

    vec4 diffuse_color = vec4(point.diffuse, 1.0) * texture(diffuse, textCoord) * diffuseFactor;

    return diffuse_color;
}





vec4 calculatePointSpecular(PointLight point)
{
    vec3 lightDir     = normalize(fragPos - point.position);
    vec3 reflection   = normalize(reflect(lightDir, normal));
    vec3 camDirection = normalize(camPos - fragPos);

    float specular_factor = pow( max( dot(camDirection, reflection), 0.0 ), 32);

    vec4 specular_color = vec4(point.specular, 1.0) * texture(specular, textCoord) * specular_factor;

    return specular_color;
}