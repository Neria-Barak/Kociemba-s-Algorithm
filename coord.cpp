#include "coord.hpp"

using namespace std;

class coordCubePhase1
{
    public:
        int co;  // Corner Orientation Coordinate
        int eo;  // Edge Orientation Coordinate
        int uds; // UDSlice Coordinate

        // constructor
        coordCubePhase1(int co,
                        int eo,
                        int uds)
        {
            this->co = co;
            this->eo = eo;
            this->uds = uds;
        }

        // constructor
        coordCubePhase1(array<int, 8> co,
                        array<int, 12> eo,
                        array<int, 12> uds)
        {

            this->setEdgeOri(eo);
            this->setCornerOri(co);
            this->setUDSlicePhase1(uds);
        }

        void setEdgeOri(array<int, 12> eo)
        {
            int s = 0;
            // we use base 2 where each bit coresspondes to an edge orientation
            for (int e = UR; e < BR; e++)
            {
                // multiplying by two at every iteration to form the number digit by digit
                s = 2 * s + eo[e];
            }
        }
        void setCornerOri(array<int, 8> co)
        {
            int s = 0;
            // we use base 3 where each bit coresspondes to an edge orientation
            for (int c = URF; c < DRB; c++)
            {
                // multiplying by two at every iteration to form the number digit by digit
                s = 3 * s + co[c];
            }
        }
        // Combination function C(n, k)
        static int C(int n, int k)
        {
            if (k > n)
                return 0;
            if (k == 0 || k == n)
                return 1;

            k = min(k, n - k); // Use symmetry to minimize iterations
            long long result = 1;

            for (int i = 1; i <= k; ++i)
            {
                result = result * (n - i + 1) / i;
            }

            return static_cast<int>(result);
        }

        static int getUDSliceCoord(array<int, 12> ep) {
            array<bool, 12> occupied = {false};
            for (int ed = UR; ed <= BR; ed++)
            {
                if (ep[ed] >= FR)
                {
                    occupied[ed] = true;
                }
            }

            int s = 0;
            int k = 3;  // 4 pieces for UDSlice - 1 since we're using 0-based index
            int n = 11; // Start from the end

            while (k >= 0)
            {
                if (occupied[n])
                {
                    --k;
                }
                else
                {
                    s += C(n, k);
                }
                --n;
            }
            return s;
        }

        void setUDSlicePhase1(array<int, 12> ep)
        {
            this->uds = coordCubePhase1::getUDSliceCoord(ep);
        }
};

class coordCubePhase2
{
    int cp;  // Corner Permutation Coordinate
    int ep;  // Edge Permutation Coordinate
    int uds; // UDSlice Coordinate

    // constructor
    coordCubePhase2(int cp,
                    int ep,
                    int uds)
    {

        this->cp = cp;
        this->ep = ep;
        this->uds = uds;
    }

    void setEdgePerm(array<int, 12> ep)
    {
        int x = 0;
        for (int e1 = BR; e1 > UR; e1--)
        {
            int s = 0;
            for (int e2 = e1 - 1; e2 >= UR; e2--)
            {
                if (ep[e2] > ep[e1])
                    s++;
            }
            x = (x + s) * e1;
        }
        this->ep = x;
    }
    void setCornerPerm(array<int, 8> cp)
    {
        int x = 0;
        for (int c1 = DRB; c1 > URF; c1--)
        {
            int s = 0;
            for (int c2 = c1 - 1; c2 >= URF; c2--)
            {
                if (cp[c2] > cp[c1])
                    s++;
            }
            x = (x + s) * c1;
        }
        this->cp = x;
    }

    // Combination function C(n, k)
    int C(int n, int k)
    {
        if (k > n)
            return 0;
        if (k == 0 || n == k)
            return 1;
        return C(n - 1, k - 1) + C(n - 1, k);
    }

    int UDSliceCoordSorted(array<int, 12> ep)
    {
        array<int, 4> arr;
        int j = 0;
        for (int e = UR; e <= BR; e++)
        {
            int ed = ep[e];
            if (ed == FR || ed == FL || ed == BL || ed == BR)
            {
                arr[j] = ed;
                j++;
            }
        }

        // mapping every order of UDSlice to a unique coordinate
        int x = 0;
        for (int j = 3; j > 0; j--)
        {
            int s = 0;
            for (int k = j - 1; k >= 0; k--)
            {
                if (arr[k] > arr[j])
                {
                    s++;
                }
            }
            x = (x+s)*j;
        }
        // Result:= UDSliceCoord*24 + x;
        this->uds =  coordCubePhase1::getUDSliceCoord(ep)*24 + x;
    }
};

// int main() {
//     cout << setCornerPerm({DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR}) << endl;
// }