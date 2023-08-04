#include <GL/freeglut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

float m[2] = {0.0f, 0.00f};
int last = 1;

//  16-15-14-13  ]
//   |        |  ]
//  17 5-4-3 12  ]
//   | |   |  |  ]----> interval=4
//  18 6 1-2 11  ]
//   | |      |  ]
//  19 7-8-9-10  ]
//   |   ----->
//  20   direction

// should the direction be changed?
bool dirChange = false;

vector<string> currentDir = {"px", "py", "nx", "ny"};

// to iterate through currentDir
int currentDirIter = 0;

// interval between direction changes, i.e, number of points gone by between each direction change.
int interval = 1;

// How many direction changes happened with the same interval length? and increment interval after this has value 2
int countSameInterval = 0;

//  lines 38 to 115 taken from geeks for geeks miiller rabin test
//  Utility function to do modular exponentiation.
//  It returns (x^y) % p

int power(int x, unsigned int y, int p)
{
    int res = 1; // Initialize result
    x = x % p;   // Update x if it is more than or
                 // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns true if n is
// probably prime.
// d is an odd number such that  d*2 = n-1
// for some r >= 1
bool miillerTest(int d, int n)
{
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    int a = 2 + rand() % (n - 4);

    // Compute a^d % n
    int x = power(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }

    // Return composite
    return false;
}

// It returns false if n is composite and returns true if n
// is probably prime.  k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(int n, int k)
{
    // Corner cases
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    // Find r such that n = 2^d * r + 1 for some r >= 1
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // Iterate given number of 'k' times
    for (int i = 0; i < k; i++)
        if (!miillerTest(d, n))
            return false;

    return true;
}

void ulamSpiral()
{
    glPointSize(3.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    for (int i = 1; i < 10000; i++)
    {
        if (i % 10 == 1 || i % 10 == 3 || i % 10 == 7 || i % 10 == 9)
        {
            if (isPrime(i, 1000))
            {
                glBegin(GL_POINTS);
                glVertex3f(m[0], m[1], 0);
                glEnd();
                glFlush();
            }
        }

        // glBegin(GL_POINTS);
        // glVertex3f(m[0], m[1], 0);
        // glEnd();
        // glFlush();

        if (i - last == interval)
        {
            dirChange = true;
            last = i;
            countSameInterval++;
        }

        if (countSameInterval == 2)
        {
            interval++;
            countSameInterval = 0;
        }

        if (dirChange)
        {
            currentDirIter += 1;
            currentDirIter %= 4;

            if (currentDirIter == 0)
            {
                m[0] += 0.005;
            }
            else if (currentDirIter == 1)
            {
                m[1] += 0.005;
            }
            else if (currentDirIter == 2)
            {
                m[0] -= 0.005;
            }
            else if (currentDirIter == 3)
            {
                m[1] -= 0.005;
            }
            dirChange = false;
        }

        else
        {
            if (currentDirIter == 0)
            {
                m[0] += 0.005;
            }
            else if (currentDirIter == 1)
            {
                m[1] += 0.005;
            }
            else if (currentDirIter == 2)
            {
                m[0] -= 0.005;
            }
            else if (currentDirIter == 3)
            {
                m[1] -= 0.005;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glGetError();
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(10000, 10000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Printing the Primes in Ulam Spiral");
    glutDisplayFunc(ulamSpiral);
    glutMainLoop();

    return 0;
}
