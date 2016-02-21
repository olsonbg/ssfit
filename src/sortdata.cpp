#include <vector>
#include <algorithm>

void sortdata( std::vector< std::vector< double > > pvtd,
               std::vector< std::vector< double > > *pts,
               std::vector< double > *volumes,
               std::vector< double > *variances)
{
	// Sort pvtd by P, sub-sorted by T.
	std::sort( pvtd.begin(), pvtd.end(),
	           [](const std::vector< double >& a, const std::vector< double >&b)
	             { return (a[0] == b[0])?a[2] < b[2]:a[0] < b[0]; } );

	for( unsigned int i=0; i < pvtd.size(); ++i)
	{
		std::vector< double> pt = { pvtd[i][0], pvtd[i][2] };
		pts->push_back( pt );

		volumes->push_back( pvtd[i][1] );
		variances->push_back( pvtd[i][3] );
	}
}
