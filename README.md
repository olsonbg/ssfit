ssfit
=====

A program to calculate the scaling parameters of the Simha-Somcynsky (SS)
equation of state (EOS). The source code is hosted by GitHub at
[https://www.github.com/olsonbg/ssfit](https://github.com/olsonbg/ssfit)

# Contents

  * [Description](#description)
  * [Required Libraries](#libraries)
  * [Installation](#installation)
  * [Usage](#usage)
  * Output
    * [summary](#save)
    * [PVTVy](#save)
    * [PVTy](#yonly)
    * [TVV](#save)
    * [curves](#curves)


**NOTE:** Github does not render LaTeX equations in markdown; to see the
equations try viewing this file, or generating the
[documentation](#documentation), on your own system.  You can also view the
html rendered from this file at
[docs/include/README.md.html](docs/include/README.md.html)

# Description

The Simha-Somcynsky equation of state, in terms of reduced variables
$\widetilde{P}$, $\widetilde{V}$, $\widetilde{T}$:

<a name="scaling"></a>
\begin{equation}
\widetilde{P} = \frac{P}{P^*}
\end{equation}

\begin{equation}
\widetilde{V} = \frac{V}{V^*}
\end{equation}

\begin{equation}
\widetilde{T} = \frac{T}{T^*}
\end{equation}

are given by equation (2) from Leszek Utracki, Robert Simha *Macromol. Theory
Simul.* **2001**, 10, 17-24:

<a name="sseos-01"></a>
\begin{equation}
  \frac{\widetilde{P}\widetilde{V}}{\widetilde{T}} - \frac{1}{1 - \eta} - \frac{2yQ^2}{\widetilde{T}}\left(AQ^2 - B\right) = 0 \qquad \mathrm{(Eq.~1)}
\end{equation}

and equation (3) from Leszek Utracki, Robert Simha *Macromol. Theory Simul.*
**2001**, 10, 17-24:

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

<a name="chi2"></a>
\begin{equation}
\chi^2 = \sum_{i=1}^{N}\frac{\left(M_i - F_i\right)^2}{\nu_i}
\end{equation}

where $M$ and $F$ are the measured and fit specific volumes, respectively,
and $\nu$ is the variance in the measured specific volumes (square of the
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

Instead of the exact equation, approximate solutions to the SS-EOS may be
determined by using equation (10) from Leszek Utracki, Robert *Simha Macromol.
Theory Simul.* **2001**, 10, 17-24:

<a name="sseos-03"></a>
\begin{equation}
\ln \widetilde{V} = a_0 + a_1\widetilde{T}^{3/2} + \widetilde{P}\left[ a_2 + \left( a_3 + a_4\widetilde{P} + a_5\widetilde{P}^2\right)\widetilde{T}^2\right] \qquad \mathrm{(Eq.~3)}
\end{equation}

where the the reduced variables are as defined [previously](#scaling), and
the constants are

| Variable  | Value   |
| --------- | -----:  |
| $a_0$ |-0.10346 |
| $a_1$ |  23.854 |
| $a_2$ | -0.1320 |
| $a_3$ |  -333.7 |
| $a_4$ |  1032.5 |
| $a_5$ | -1329.9 |


# <a name="libraries"></a>Required Libraries

## [GNU Scientific Library](http://www.gnu.org/software/gsl/) (GSL)

Used for root finding.

## [Minuit2](http://project-mathlibs.web.cern.ch/project-mathlibs/minuit/release/download.html)

Used for minimizing $\chi^2$.


# Installation

To compile the program

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=release ..
make
src/ssfit
```

<a name="documentation"></a> To generate the documentation as html, which
will be available at `docs/html/index.html`, use

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
|[pstar](#Xstar)                <a name="pstar-t"></a>       |   p        | real number   | yes       | Initial $P^*$ value to use for fitting|
|[vstar](#Xstar)                <a name="vstar-t"></a>       |   v        | real number   | yes       | Initial $V^*$ value to use for fitting|
|[tstar](#Xstar)                <a name="tstar-t"></a>       |   t        | real number   | yes       | Initial $T^*$ value to use for fitting|
|[ranges](#ranges)              <a name="ranges-t"></a>      |   r        | string        | no        | Valid temperature ranges, for each pressure to use |
|[pranges](#pranges)            <a name="pranges-t"></a>     |   R        | string        | no        | Valid pressure ranges, for each temperature to use |
|[yonly](#yonly)                <a name="yonly-t"></a>       |   y        |               | no        | Fit only $y$ values, $P^*$, $V^*$, and $T^*$ are fixed.
|[blockdata](#blockdata)        <a name="blockdata-t"></a>   |   b        |               | no        | Input PVT data is in block format |
|[save](#save)                  <a name="save-t"></a>        |   s        | string        | no        | Prefix used for saving data |
|[fixp](#fixX)                  <a name="fitp-t"></a>        |            |               | no        | Fix Pstar to the value specified on the command line|
|[fixv](#fixX)                  <a name="fitv-t"></a>        |            |               | no        | Fix Vstar to the value specified on the command line|
|[fixt](#fixX)                  <a name="fitt-t"></a>        |            |               | no        | Fix Tstar to the value specified on the command line|
|[dataonly](#dataonly)          <a name="dataonly-y"></a>    |   d        |               | no        | Save the data in easy to plot files. This will not do any fitting |
|data                                                        |            |               | no        | Synonym for [dataonly](#dataonly-t)|
|[scan](#scan)                  <a name="scan-t"></a>        |            |               | no        | Scan the fitting parameters around the minimum after an initial fitting, followed by a second round of fitting|
|[curves](#curves)              <a name="curves-t"></a>      |            |               | no        | Generate curves for nice plotting (see [numpoints](#numpoints-t) option)|
|[approximate](#approximate)    <a name="approx-t"></a>      |            |               | no        | Use an approximate equation for fitting|
|approx                                                      |            |               | no        | Synonym for [approximate](#approx-t)|
|[kelvin](#kelvin)              <a name="kelvin-t"></a>      |            |               | no        | The input temperature are in Kelvin. The default is Celsius|
|[numpoints](#numpoints)        <a name="numpoints-t"></a>   |   n        | integer       | no        | Number of points to use for curve generation|



## Input

Read PVT data that is in three column format, with columns separated by
whitespace.

  - Columns
    1. Measured pressure
    1. Measured temperature
    1. Measured specific volume

## Blockdata

Read PVT data that is in block format, with columns separated by whitespace.

| Column 1 | Column 2 | Column 3 | .... | Column n |
| :------: | :------: | :------: | :--: | :------: |
|          |    P1    |    P2    |  ... |    Pn    |
|    T1    |    V11   |    V12   |  ... |    V1n   |
|    T2    |    V21   |    V22   |  ... |    V2n   |
|    ...   |    ...   |    ...   | ...  |    V2n   |
|    Tm    |    Vm1   |    Vm2   | ...  |    Vmn   |

## Ranges
Read temperature ranges. Fitting and curve generation will be limited to
temperature ranges listed in this file.

Data is in three column format, with each column separated by whitespace.

  - Columns
    1. Pressure
    1. Minimum temperature
    1. Maximum temperature

## PRanges
Read pressure ranges. Curve generation will be limited to pressure ranges
listed in this file.

Data is in three column format, with each column separated by whitespace.

  - Columns
    1. Temperature
    1. Minimum pressure
    1. Maximum pressure


## yonly

For temperatures below the glass transition, the SS-EOS equilibrium equation
[(2)](#sseos-02) is not valid. This makes determining $P^*$, $V^*$, and
$T^*$ difficult, however the $y$ values can be determined from equation
[(1)](#sseos-01), if the scaling parameters are known. This option enables
determining $y$ by fixing the scaling parameters, and using only equation
[(1)](#sseos-01).

Default name of output file: `default-PVTy.dat`

  - Columns of output file
    1. Measured pressure
    1. Measured specific volume
    1. Measured temperature
    1. Fit occupied fraction of lattice sites

##  <a name="Xstar"></a> pstar, vstar, and tstar

The initial guess for the scaling parameters of the [SS-EOS](#scaling). All
three have the same units as the parameter they are scaling.

## <a name="fixX"></a> fixp, fixv, and fixt

The default behavior is to use $P^*$, $V^*$, and $T^*$ as fitting
parameters, however one, two or all three parameters may be fixed with these
options.

## Dataonly

Do not fit the data, only save it or generate [curves](#curves) from the
$P^*$, $V^*$, and $T^*$ [parameters](#Xstar).

## Scan

After an initial minimization of [$\chi^2$](#chi2), the free parameters will
be scanned around their current values in an attempt to refine the minimum.
A second round of minimization will then be performed using the results of
the scan as initial values for the free parameters.

## Curves

Generate curves, for specific volume ($V$) and occupied fraction
of lattice sites ($y$), containing [numpoints](#numpoints) data points for
all pressures and temperatures specified in the [ranges](#ranges) file.

Default name of output file: `default-curves-TVy.dat`

  - Columns of output file
    1. Measured temperature
    1. Specific volume from fit
    1. Occupied fraction of lattice sites
  - Data is grouped by pressure, with each pressure separated by a blank
    line.

If the [pranges](#pranges) option is specified, the following curve file
will also be generated:

Default name of output file: `default-curves-PVy.dat`

  - Columns of output file
    1. Measured pressure
    1. Measured specific volume
    1. Fit occupied fraction of lattice sites
  - Data is grouped by temperature, with each group separated by a blank
    line

The `default` string will be replaced by the string given by [save](#save),
if any.

## Approximate

The minimization is performed using the [approximate solution](#sseos-03) to
the SS-EOS, instead of the exact equations [(1)](#sseos-01) and
[(2)](#sseos-02).

## Kelvin

The temperature values in the [input](#input) and [ranges](#ranges) files are in
Kelvin, instead of the default Celsius.

## numpoints

Number of data points to save for [curve](#curves) generation.

## save

Prefix used for saving data. If no save prefix is used, the string `default`
will be used. The default files generated are listed below.

  - `default-summary.dat`
  - `default-PVTVy.dat`
      - Columns
          1. Measured pressure
          1. Measured specific volume
          1. Measured temperature
          1. Fit specific volume
          1. Fit occupied fraction
  - `default-TVV.dat`
      - Columns
          1. Measured temperature
          1. Measured specific volume
          1. Fit specific volume
      - Data is grouped by pressure, with each group separated by a blank
        line.
