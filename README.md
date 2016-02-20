ssfit
=====

A program to calculate the reducing parameters of the Simha-Somcynsky (SS)
equation of state (EOS).

SS equations, in terms of reduced variables $\widetilde{P}$, $\widetilde{V}$,
$\widetilde{T}$:

\begin{equation}
\widetilde{P} = \frac{P}{P^*}
\end{equation}

\begin{equation}
\widetilde{V} = \frac{V}{V^*} \\
\end{equation}

\begin{equation}
\widetilde{T} = \frac{T}{T^*}
\end{equation}

are given by equation (2) from Leszek Utracki, Robert Simha Macromol. Theory Simul. 2001, 10, 17-24:

<a name="sseos-01"></a>
\begin{equation}
  \frac{\widetilde{P}\widetilde{V}}{\widetilde{T}} - \frac{1}{1 - \eta} - \frac{2yQ^2}{\widetilde{T}}\left(AQ^2 - B\right) = 0 \qquad \mathrm{(Eq.~1)}
\end{equation}

and equation (3) from Leszek Utracki, Robert Simha Macromol. Theory Simul. 2001, 10, 17-24:

<a name="sseos-02"></a>
\begin{equation}
 3c\left[\frac{\eta - \frac{1}{3}}{1 - \eta} - \frac{yQ^2}{6\widetilde{T}}\left(3AQ^2 -2B\right)\right] + \left(2-s\right) - \frac{s}{y}\ln\left(1-y\right) = 0 \qquad \mathrm{(Eq.~2)}
\end{equation}

Where,
\begin{equation}
    Q = \frac{1}{y\widetilde{V}}
\end{equation}

\begin{equation}
   \eta = 2^{-1/6}yQ^{1/3}
\end{equation}
\begin{equation} A = 1.011 \end{equation}
\begin{equation} B = 1.2045 \end{equation}

The program minimizes $\chi^2$, with the fit parameters $P^*$, $V^*$, and
$T^*$:
\begin{equation}
\chi^2 = \sum_{i=0}^{N}\frac{\left(M_i - F_i\right)^2}{\sigma_i}
\end{equation}
where $M$ and $F$ are the measured and fit specific volumes, respectively,
and $\sigma$ is the variance in the measured specific volumes (square of the
standard deviation).

The reduced specific volume ($\widetilde{V}$), and fraction of
occupied lattice sites ($y$) are determined from equation [(2)](#sseos-02),
using the following constraints:

\begin{equation}
  \frac{s}{3c}\simeq1
\end{equation}

\begin{equation}
  s\gg1
\end{equation}

# Contents

  * [Required Libraries](#libraries)
  * [Installation](#installation)
  * [Usage](#usage)
  * [Output](#output)
    * summary
    * PVTVy
    * TVV
    * curves-PVy


# <a name="libraries"></a>Required Libraries

## [GNU Scientific Library](http://www.gnu.org/software/gsl/) (GSL)

Used for root finding.

## [Minuit2](http://project-mathlibs.web.cern.ch/project-mathlibs/minuit/release/download.html)

Used for minimizing chi squared.


# Installation

To compile the program

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=release ..
make
src/ssfit
```

To generate the documentation as html, which will be available at
`docs/html/index.html`, use

```bash
make docs
```

To cross-compile, use your toolchain cmake file as:

```bash
cmake -DCMAKE_BUILD_TYPE=release -DCMAKE_TOOLCHAIN_FILE=<Toolchain cmake file> ..
```

# Usage

A typical command line would look like this:

```bash
ssfit -i data/PPE-PS/60.dat -r data/PPE-PS/60-ranges.dat -p 8425 -v 0.9065 -t 11434 --blockdata -s PPE-PS60 --curves
```

Below is a table of all options available from the command line. The long
form options are preceded with `--`, and short form a single `-`. For
options with both a long and short form, either one may be used on the
command line.



|Long form                                                   | Short form |Option Type    | Required? | Description |
|:-----------------------------------------------------------|:----------:|:--------------|:---------:|:------------|
|[input](#input)                <a name="input-t"></a>       |   i        | string        | yes       | Input PVT data file|
|[pstar](#pstar)                <a name="pstar-t"></a>       |   p        | real number   | yes       | Initial Pstar value to use for fitting|
|[vstar](#vstar)                <a name="vstar-t"></a>       |   v        | real number   | yes       | Initial Vstar value to use for fitting|
|[tstar](#tstar)                <a name="tstar-t"></a>       |   t        | real number   | yes       | Initial Tstar value to use for fitting|
|[ranges](#ranges)              <a name="ranges-t"></a>      |   r        | string        | no        | Valid temperature ranges, for each pressure to use |
|[blockdata](#blockdata)        <a name="blockdata-t"></a>   |   b        |               | no        | Input PVT data is in block format |
|[fixp](#fixp)                  <a name="fitp-t"></a>        |            |               | no        | Fix Pstar to the value specified on the command line|
|[fixv](#fixv)                  <a name="fitv-t"></a>        |            |               | no        | Fix Vstar to the value specified on the command line|
|[fixt](#fixt)                  <a name="fitt-t"></a>        |            |               | no        | Fix Tstar to the value specified on the command line|
|[dataonly](#dataonly)          <a name="dataonly-y"></a>    |   d        |               | no        | Save the data in easy to plost files. This will not do and fitting |
|data                                                        |            |               | no        | Synonym for [dataonly](#dataonly-t)|
|[scan](#scan)                  <a name="scan-t"></a>        |            |               | no        | Scan the fitting parameters around the minimum after an initial fitting, followed by a second round of fitting|
|[curves](#curves)              <a name="curves-t"></a>      |            |               | no        | Generate curves for nice plotting (see [numpoints](#numpoints-t) option)|
|[approximate](#approximate)    <a name="approx-t"></a>      |            |               | no        | Use an approximate equation for fitting|
|approx                                                      |            |               | no        | Synonym for [approximate](#approx-t)|
|[kelvin](#kelvin)              <a name="kelvin-t"></a>      |            |               | no        | The input temperature are in Kelvin. The default is Celsius|
|[numpoints](#numpoints)        <a name="numpoints-t"></a>   |   n        | integer       | no        | Number of points to use for curve generation|



# Output

Depending upon the command line options, many data files may be generated.
The description of all calculations are listed below
