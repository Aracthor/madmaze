# Madmaze

This project is mainly made from a code that I did a long time ago. So please do not judge me too hardly on the code.

Please concentrate on possibilities: there are many kind of mazes that you can create with this program. Just follow the instructions below.


## Compilation

This project use [pargse library](https://github.com/Aracthor/pargse) in order to work.

Once you installed it, you can compile this project as any CMake project:

    mkdir build
	cd build
	cmake ..
	make


## Execution

You have to give as parameters at least generation method, width and height for your maze:

    ./madmaze random|lines|islands -x width -y height

You will find details about random, lines and islands algorithms below. But there are several other additional options that you can modify with arguments, in order of your preference:

- `-o`: define output file name. Default name is `a.txt`.
- `-b`: define number of entrances. Default value is 1.
- `-e`: define number of ends. Default value is 1.
- `-w`: define character that will represent an obstacle. Default value is `#`.
- `-p`: define character that will represent a path. Default value is ` `.
- `-B`: define character that will represent a begin. Default value is `1`.
- `-E`: define character that will represent an end. Default value is `2`.
- `-s`: without parameter. This flag will display the file content once generated.
- `-d`: without parameter. This flag will display the maze generation in slow motion.


### Random generation

This simple generation will simply randomly choose path or wall for every tile from a defined percentage.  
You must define percentage in an additional parameter with `-P` flag, else it would be set to 0, and your maze shall be a big empty room.

    ./madmaze random -x 20 -y 10 -P 42 -d

    ####################
    ## #     ###  #   ##
    #  # ##    # # #####
    #  ###  ##   ##   ##
    ##1   #    #  # ## #
    ##      ##    #   2#
    ###       ### # ## #
    #  #   #        # ##
    # ### # ## # #  ## #
    ####################

**Note**: as it is totaly random, nothing garantee you that your maze will be feasible or not.


### Lines algorithm

This quite simple generation will start from one of your entrances, and cut horizontal or vertical corridors through a maze full of walls, then insert one of your ends once it finished.  
You must define a precise path tiles number for this algorithm with `-S`, else there would be no path and your maze shall be a big full room.

    ./madmaze lines -x 30 -y 15 -S 42 -d

    ##############################
    ##############################
    #                            #
    # ######## ############### ###
    # ######## ##############   ##
    # ######## ##############   ##
    # ######## ##############   ##
    # ########                  ##
    # ######## ### ###########  ##
    #     1### ### ###########  ##
    ########## ### ###########  ##
    ########## ###             2##
    ########## ###################
    ########## ###################
    ##############################


### Islands algorithm

This generation shall create random-shaped rooms - islands - linked by diagonal corridors.  
You must define two parameters: `-N` for islands number, and `-I` for islands size (in number of path tile).  
Begin and end won't be on the same island, so you have to generate at least two of them.

    ./madmaze islands -x 40 -y 20 -N 5 -I 15 -d

    ########################################
    ######### ########## ###################
    #########  ########      ###############
    ######## 2  ######     #    ############
    #######      ###   #    ###    ###  # ##
    ####### #   ###  ###   #######         #
    ######    ####  #################    ###
    ###### #####   #################     ###
    #####  ####  ##################  # #####
    ####  ####  ##################  ########
    #### ####  ##################  #########
    ###  ##   ################### ##########
    ### ##  ####################  ##########
    ##  #  ####################  ###########
    ##    ####################  ############
    #   ####################   #############
    #     #################    #############
    #    # ###############   1  ############
    #       ################    ############
    ########################################

**Note**: For a generation close of the lines one but with diagonal corridors, you can use this algorithm with islands size set to 0:

    ./madmaze islands -x 40 -y 20 -N 10 -I 0 -d

    ########################################
    ########################################
    ########################################
    ########################################
    ##########################1#############
    ##########   #############  ############
    #########  #  ######  ##### ##     #####
    ########  ###  ####  #####      ########
    ######   ##### ###  ###       ##########
    #####  #######  #          ## ##########
    ####  #########     #    ####  #########
    ####    ####      #   ########  ########
    #######      #      ########### ########
    #####    ##        ############  #######
    #####2######    ## #############  ######
    ############ #####  ############# ######
    ###################  ######        #####
    ####################        ############
    ####################  ##################
    ########################################
