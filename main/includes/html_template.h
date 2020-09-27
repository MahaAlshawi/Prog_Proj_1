/*
 * html_template.h
 *
 *  Created on: Sep 26, 2020
 *      Author: cs58
 */

#ifndef INCLUDES_HTML_TEMPLATE_H_
#define INCLUDES_HTML_TEMPLATE_H_

#define HEAD "<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <title>My Photo Album</title>\
    <style>\
        body {\
			margin: 40px;\
		}\
		.wrapper {\
			display: grid;\
			grid-gap: 100px;\
			grid-template-columns: repeat(auto-fill, minmax(200px, 1fr) ) ;\
			background-color: #fff;\
			color: #F44;\
		}\
		.box {\
			display: flex; \
			flex-direction: column;\
			align-items: center; \
			justify-content: center;\
			border-radius: 5px;\
			padding: 10px;\
			\
		}\
		h2{\
		font-size:15px;\
		text-align: center;\
		}\
		\
    </style>\
</head>\
<body>\
    <h1>Photo Album</h1>\
    <p>Click any of the photos below to display in full resolution.</p>\
	<div class=\"wrapper\">"


#define TAIL "	</div>\
</body>\
</html>"

#define REP1 "		<div class=\"box\">\
			<h2>"
#define REP2 "</h2>\
			<a href=\"./destination4/"
#define REP3 "\"><img src=\"./destination2/"
#define REP4 "\" border=\"1\"></a>\
		</div>"
#endif /* INCLUDES_HTML_TEMPLATE_H_ */
