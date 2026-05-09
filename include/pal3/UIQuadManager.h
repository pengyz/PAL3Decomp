#pragma once

class gbRefObject;  // defined in gbengine/gbTexture.h

class UIQuadManager {
public:
    char m_base[16];
    gbRefObject *m_pTexture[3];

    void Destroy(void);
};
