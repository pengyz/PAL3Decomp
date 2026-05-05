#include "ORect.h"

ORect::ORect()
{
    m_numpt = 0;
}

ORect::~ORect()
{
}

bool ORect::IsOK()
{
    return m_numpt >= 3;
}

void ORect::Clear()
{
    m_numpt = 0;
}

void ORect::AddPoint(int x, int y)
{
    if (m_numpt >= 4)
        return;
    m_pt[m_numpt].x = x;
    m_pt[m_numpt].y = y;
    m_numpt++;
}

void ORect::GetRangeX(int *minx, int *maxx)
{
    if (m_numpt == 0)
        return;
    int mn = m_pt[0].x;
    int mx = m_pt[0].x;
    for (int i = 1; i < m_numpt; i++) {
        if (m_pt[i].x < mn) mn = m_pt[i].x;
        if (m_pt[i].x > mx) mx = m_pt[i].x;
    }
    *minx = mn;
    *maxx = mx;
}

bool ORect::LineSeg(int x, tagPOINT *pt1, tagPOINT *pt2, int *y)
{
    if (pt1->x == pt2->x)
        return false;
    if (x < pt1->x && x < pt2->x)
        return false;
    if (x > pt1->x && x > pt2->x)
        return false;
    *y = pt1->y + (pt2->y - pt1->y) * (x - pt1->x) / (pt2->x - pt1->x);
    return true;
}

bool ORect::GetRangeY(int x, tagRECT *cliprect, int *miny, int *maxy)
{
    if (m_numpt < 3)
        return false;

    int yvals[8];
    int nyvals = 0;

    for (int i = 0; i < m_numpt; i++) {
        int next = (i + 1) % m_numpt;
        int y;
        if (LineSeg(x, &m_pt[i], &m_pt[next], &y)) {
            if (nyvals < 8)
                yvals[nyvals++] = y;
        }
    }

    if (nyvals < 2)
        return false;

    int mn = yvals[0];
    int mx = yvals[0];
    for (int i = 1; i < nyvals; i++) {
        if (yvals[i] < mn) mn = yvals[i];
        if (yvals[i] > mx) mx = yvals[i];
    }

    if (cliprect) {
        if (mn < cliprect->top) mn = cliprect->top;
        if (mx > cliprect->bottom) mx = cliprect->bottom;
    }

    *miny = mn;
    *maxy = mx;
    return mn <= mx;
}
