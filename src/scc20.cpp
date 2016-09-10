int main(int argc[], int argv[])
{
soup.settings.init(&argc,&argv); // settings from settings file, goals etc.
soup.initGoals(); // make something out of the settings goals
soup.init();
while(!soup.complete)
{
	soup.run(); //make a run and put the best one in statistics
	io.print(soup.statistics,RUN);		
}

soup.make_additional_statistics();
io.print(soup.statistics,FINAL); // file/screen
io.save(soup.statistics);
}


