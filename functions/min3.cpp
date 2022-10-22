double min3(double &a, double &b, double &c) //求三个数中最小的
{
	double min=a;
	if (b<min)
	{
		min=b;
	}
	if (c<min)
	{
		min=c;
	}
	return min;
}
