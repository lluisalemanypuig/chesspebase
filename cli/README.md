# Chess Puzzle Database explorer -- Command Line Interface

Use the chess database explorer via a command line. Run the program by feeding it the path to the various databases you want to load. For example,

    $ ./cli/cli --lichess-database lichess.csv

Or, you can load the databases by using the `load` command,

    option> load

You can use the `info` command to see some basic statistics of the database, such as the total number of __unique__ loaded positions.

Once it has finished loading, you can specify the query you want to run by using the `query` command:

    option> query

The application will prompt you with the different questions you can make, and specify
- the number of a specific piece (pawn, rook, knight, bishop, queen) of a specific player (White, Black),
- the number of a specific piece in total, that is, for both White and Black,
- the turn of a player, so this way you can search for positions where it is Black to move.

Use the command `show` once you are done with your query to make sure what you wrote is correct. Then, use the `run` command to execute the query.
