
uniform vec2 lightPositions[10]; 
uniform float lightRadiuss[10];     

void main()
{
    vec2 fragPosition = gl_FragCoord.xy; 

    float minDistance = 99999.0;

   
    for (int i = 0; i < 10; ++i) { 
        float distance = length(fragPosition - lightPositions[i]);
        float normalizedDistance = distance / lightRadiuss[i];
        minDistance = min(minDistance, normalizedDistance);
    }

    //La lumière la plus proche détermine si le pixel est visible
    gl_FragColor.a = minDistance;
}