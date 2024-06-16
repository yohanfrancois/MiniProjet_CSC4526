
uniform vec2 lightPositions[10]; 
uniform float lightRadiuss[10];     

void main()
{
    vec2 fragPosition = gl_FragCoord.xy; 

    float minAlpha = 99999.0;

   
    for (int i = 0; i < 10; ++i) { 
        float distance = length(fragPosition - lightPositions[i]);
        float alpha = distance / lightRadiuss[i];
        minAlpha = min(minAlpha, alpha);
    }

    //La lumi�re la plus intense d�termine l'alpha du pixel
    gl_FragColor.a = minAlpha;
}