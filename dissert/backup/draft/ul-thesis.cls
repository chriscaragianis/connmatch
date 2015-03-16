%
% Change History:
%
% 2010-10-15 Created
%
\ProvidesClass{ul-thesis}[2010/10/22]
\def\ULt@fname{ul-thesis.cls}

% Options
\RequirePackage{xkeyval}
\RequirePackage{ifthen}
%
% [final] disables line numbering, colors links black, and passes to showlabels
\define@boolkey{\ULt@fname}[ULt@]{final}[true]{}
\setkeys{\ULt@fname}{final=false}
%
% [debug] displays indentation markings and a 1-inch grid
\define@boolkey{\ULt@fname}[ULt@]{debug}[true]{}
\setkeys{\ULt@fname}{debug=false}
%
% [index] controls the index
\define@boolkey{\ULt@fname}[ULt@]{index}[true]{}
\setkeys{\ULt@fname}{index=true}
\DeclareOptionX{noindex}{%
	\setkeys{\ULt@fname}{index=false}%
	\XKV@useoption{noindex}%
}
%
% [glossary] controls the glossary
\define@boolkey{\ULt@fname}[ULt@]{glossary}[true]{}
\setkeys{\ULt@fname}{glossary=true}
\DeclareOptionX{noglossary}{%
	\setkeys{\ULt@fname}{glossary=false}%
	\XKV@useoption{noglossary}%
}
%
% [bardef] puts a bar on the left side of definitions
\define@boolkey{\ULt@fname}[ULt@]{bardef}[true]{}
\setkeys{\ULt@fname}{bardef=false}
%
% [fancyproof] replaces the QED symbol with a complete graph and adds ending marks for cases
\define@boolkey{\ULt@fname}[ULt@]{fancyproof}[true]{}
\setkeys{\ULt@fname}{fancyproof=false}
%
% [fontloader] allows you to pick a set of font loaders
\define@choicekey*{\ULt@fname}{fontloader}[\val@fontloader\nr]{none,base,fontspec,mathspec,unicode-math}{}
\setkeys{\ULt@fname}{fontloader=mathspec}
%
% [textfont] sets the font to be used for text
\DeclareOptionX{textfont}{%
	\def\temptyA{#1}
	\ifx\temptyA\empty%
		\ClassError{ul-thesis}{The textfont option requires a font name}{Example: \protect\documentclass[textfont=TeX Gyre Termes]\{...}
	\else
		\providecommand*{\ULt@textfont}{TeX Gyre Termes}%
		\renewcommand*{\ULt@textfont}{#1}%
	\fi
}
%
% [mathfont] sets the font to be used for text
\DeclareOptionX{mathfont}{%
	\def\temptyA{#1}
	\ifx\temptyA\empty%
		\ClassError{ul-thesis}{The mathfont option requires a font name}{Example: \protect\documentclass[mathfont=Zapf Dingbats]\{...}
	\else
		\providecommand*{\ULt@mathfont}{STIXGeneral}%
		\renewcommand*{\ULt@mathfont}{#1}%
	\fi
}
%
% Pass unknown options to memoir
\DeclareOptionX*{\PassOptionsToClass{\CurrentOption}{memoir}}
%
% Set some defaults to pass to memoir. Placing these before \ProcessOptionsX allows them to be overridden.
\PassOptionsToClass{12pt,letterpaper,oneside}{memoir}
\ProcessOptionsX
\LoadClass{memoir}


% geometry to set margins, etc.
\ifULt@debug
	%showframe option will draw a box around the text area
	\RequirePackage[top=1in,right=1in,bottom=1in,left=1.5in,footskip=0.5in,showframe]{geometry}
	\RequirePackage[top-left,step=1in,arrows=false]{pagegrid}
\else
	\RequirePackage[top=1in,right=1in,bottom=1in,left=1.5in,footskip=0.5in]{geometry}
\fi


% AMS packages
\RequirePackage{amsmath,amssymb}

\RequirePackage{calc}

% Font alteration
%		TeX Gyre family: Adventor, Bonum, Chorus, Cursor, Heros, Pagella, Schola, Termes
\providecommand*{\ULt@textfont}{TeX Gyre Termes}
\providecommand*{\ULt@mathfont}{STIXGeneral}

\ifthenelse{\equal{\val@fontloader}{none}}{%
}{%
	\ifthenelse{\equal{\val@fontloader}{base}}{%
		\RequirePackage[T1]{fontenc}
		\RequirePackage{lmodern}
	}{%
		\ifthenelse{\equal{\val@fontloader}{fontspec}}{%
			\RequirePackage{xltxtra}
			\defaultfontfeatures{Mapping=tex-text}
			\setmainfont{\ULt@textfont}
		}{%
			\ifthenelse{\equal{\val@fontloader}{mathspec}}{%
				\RequirePackage{mathspec}
				\RequirePackage{xltxtra}
				\defaultfontfeatures{Mapping=tex-text}
				\ifthenelse{\equal{\ULt@textfont}{\ULt@mathfont}}{
					\setallmainfonts{\ULt@mathfont}
				}{
					\setmathsfont(Digits,Latin,Greek,Special){\ULt@mathfont}
					\setmathrm{\ULt@mathfont}
					\setmainfont{\ULt@textfont}
				}
			}{%
				\RequirePackage{xltxtra}
				\RequirePackage[math-style=TeX]{unicode-math}
				\setmainfont[Mapping=tex-text]{\ULt@textfont}
				\setmathfont{\ULt@mathfont}%{xits-math.otf}
			}%
		}%
	}%
}


% makeidx for indexing
\ifULt@index
	\DisemulatePackage{makeidx}
	\let\see=\undefined
	\let\printindex=\undefined
	\RequirePackage{makeidx}
	\renewcommand{\indexname}{INDEX}
	\AtBeginDocument{\makeindex}
	\let\ULt@printindex\printindex
	\renewcommand{\printindex}{\cleardoublepage\nolinenumbers\ULt@printindex}
\fi


% biblatex for bibliography management.
\RequirePackage[style=ieee,date=iso8601,block=space,backend=biber]{biblatex}
\setlength{\biblabelsep}{0.5em}
\DeclareFieldFormat{url}{URL\addcolon\space\url{#1}}
\renewcommand*{\mkbibacro}[1]{#1}%
\let\ULt@printbibliography\printbibliography
\renewcommand{\printbibliography}{\clearpage\ULt@printbibliography[title=REFERENCES]}


% aliascnt to fix an issue with \autoref when counters are shared
\RequirePackage{aliascnt}


% yay hyperref
\ifULt@final
	\RequirePackage[colorlinks=true,citecolor=black,linkcolor=black,urlcolor=black]{hyperref}
\else
	\RequirePackage[colorlinks=true,citecolor=red!20!black,linkcolor=green!20!black,urlcolor=blue!50!black]{hyperref}
\fi
%
\newif\ifULt@UCAutoref
\ULt@UCAutoreffalse
\def\ULt@imup#1#2{\uppercase{#1}#2}
\newcommand*{\ULt@mup}[1]{\ULt@imup#1}
\newcommand*{\ULt@autorefcase}[1]{\ifULt@UCAutoref\ULt@mup{#1}\else#1\fi}
\newcommand*{\Autoref}[1]{\ULt@UCAutoreftrue\autoref{#1}\ULt@UCAutoreffalse}
%
\def\theoremautorefname{Theorem}%\ULt@autorefcase{theorem}}
\def\lemmaautorefname{Lemma}%\ULt@autorefcase{lemma}}
\def\propositionautorefname{Proposition}%\ULt@autorefcase{proposition}}
\def\corollaryautorefname{Corollary}%\ULt@autorefcase{corollary}}
\def\definitionautorefname{Definition}%\ULt@autorefcase{definition}}
\def\conjectureautorefname{Conjecture}%\ULt@autorefcase{conjecture}}
\def\exampleautorefname{\ULt@autorefcase{example}}
\def\questionautorefname{\ULt@autorefcase{question}}
\def\proofautorefname{\ULt@autorefcase{proof}}
\def\claimautorefname{\ULt@autorefcase{claim}}
\def\caseautorefname{\ULt@autorefcase{case}}
\def\equationautorefname{\ULt@autorefcase{equation}}
\def\figureautorefname{\ULt@autorefcase{figure}}
\def\tableautorefname{\ULt@autorefcase{table}}
\def\sectionautorefname{\ULt@autorefcase{section}}
%
\newcommand*{\altref}[2][label]{\hyperref[#2]{#1 \ref*{#2}}}

% glossaries package for symbol list. Needs to be after hyperref for links to work.
\ifULt@glossary
	\let\glossarymark=\undefined
	\let\printglossary=\undefined
	\let\theglossary=\undefined
	\let\endtheglossary=\undefined
	\RequirePackage[nomain,nonumberlist,toc]{glossaries}
	\newglossary{notation}{not}{nol}{GLOSSARY OF NOTATION}
	
	\newglossarystyle{twocolgloss}{
		\glossarystyle{super}
		\renewenvironment{theglossary}{%
			\tablehead{}\tabletail{}%
			\vspace{0.25\baselineskip}\begin{supertabular}{rp{\glsdescwidth}}%
		}{%
			\end{supertabular}%
		}%
		\renewcommand*{\glsgroupskip}{}
		\renewcommand*{\glspostdescription}{}
	}
	\setlength{\glsdescwidth}{0.75\textwidth}
	\AtBeginDocument{\makeglossaries}
	\glossarystyle{twocolgloss}
	\let\ULt@printglossary\printglossary
	\renewcommand{\printglossary}{\cleardoublepage\glsaddall\ULt@printglossary}
\else
	\providecommand{\@newglossary}[4]{\ClassError{ul-thesis}{.aux file still contains glossary data}{Delete your .aux file.}}
\fi


% yay tikz
% tikz needs to load before lineno to allow \draw plot table to work correctly
\RequirePackage{tikz}


% showkeys to show labels in the margin.
\ifULt@final \relax\else
	\RequirePackage[notcite,notref]{showkeys}
	\@ifpackageloaded{fontspec}{%
		\renewcommand*{\showkeyslabelformat}[1]{%
			\footnotesize\bfseries\fontspec[FakeStretch=0.85,Color=666666FF]{TeX Gyre Cursor}%
			#1%
		}%
	}{%
		\renewcommand*{\showkeyslabelformat}[1]{\footnotesize\ttfamily#1}%
	}
\fi

% lineno package for line numbering
\RequirePackage[right,mathlines]{lineno}
\@ifpackageloaded{fontspec}{%
	\renewcommand{\linenumberfont}{%
		\footnotesize\bfseries\fontspec[FakeStretch=0.85,Color=666666FF]{TeX Gyre Cursor}%
	}%
}{%
	\relax%
}
\setlength\linenumbersep{0pt}
\setlength\linenumberwidth{0.5in}
\ifULt@final \relax\else
	% adapted from http://simon.bonners.ca/blog///blog5.php/2010/10/06/line-number-and-amsmath
	\newcommand*\patchAmsMathEnvironmentForLineno[1]{%
		\expandafter\let\csname old#1\expandafter\endcsname\csname #1\endcsname
		\expandafter\let\csname oldend#1\expandafter\endcsname\csname end#1\endcsname
		\renewenvironment{#1}%
		{\linenomath\csname old#1\endcsname}%
		{\csname oldend#1\endcsname\endlinenomath}%
	}%
	\newcommand*\patchBothAmsMathEnvironmentsForLineno[1]{%
	\patchAmsMathEnvironmentForLineno{#1}%
	\patchAmsMathEnvironmentForLineno{#1*}}%
	\AtBeginDocument{%
		%\renewcommand{\[}{\begin{equation*}}
		%\renewcommand{\]}{\end{equation*}}
		\let\ULt@displaymath\[%
		\let\ULt@enddisplaymath\]%
		\renewcommand{\[}{\begin{linenomath}\ULt@displaymath}%
		\renewcommand{\]}{\ULt@enddisplaymath\end{linenomath}}%
		\patchBothAmsMathEnvironmentsForLineno{equation}%
		\patchBothAmsMathEnvironmentsForLineno{align}%
		\patchBothAmsMathEnvironmentsForLineno{flalign}%
		\patchBothAmsMathEnvironmentsForLineno{alignat}%
		\patchBothAmsMathEnvironmentsForLineno{gather}%
		\patchBothAmsMathEnvironmentsForLineno{multline}%
	}
	\linenumbers
\fi



% framed for the bardef option
\ifULt@bardef
	\RequirePackage{framed}
	\PassOptionsToPackage{framed}{ntheorem}
\fi	

% ntheorem
\RequirePackage[amsmath,thmmarks,hyperref]{ntheorem}

\setlength{\theorempreskipamount}{0pt}
\setlength{\theorempostskipamount}{0pt}

\newtheoremstyle{doug}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\ ##2\theorem@separator]}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\ ##2\ (##3)\theorem@separator]}
\newtheoremstyle{dougindent}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\ ##2\theorem@separator]}%
	{%
		\setlength{\leftskip}{\parindent}%
		\setlength{\rightskip}{\parindent}%
		\item[\hskip\labelsep \theorem@headerfont ##1\ ##2\ (##3)\theorem@separator]%
	}
\newtheoremstyle{nonumberdoug}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\theorem@separator]}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\ ##3\theorem@separator]}

\theoremstyle{doug}

\theoremheaderfont{\normalfont\bfseries}
\theorembodyfont{\normalfont}
\theoremseparator{.}
\theoremsymbol{}

\newtheorem{theorem}{Theorem}[chapter]

\theoremstyle{doug}
\newaliascnt{lemma}{theorem}
\newtheorem{lemma}[lemma]{Lemma}
\aliascntresetthe{lemma}

\newaliascnt{proposition}{theorem}
\newtheorem{proposition}[proposition]{Proposition}
\aliascntresetthe{proposition}

\newaliascnt{corollary}{theorem}
\newtheorem{corollary}[corollary]{Corollary}
\aliascntresetthe{corollary}

\ifULt@bardef
	\theoremprework{%
		\par\nobreak\noindent%
		\setlength{\theorempreskipamount}{0pt}%
		\setlength{\theorempostskipamount}{0pt}%
		\begin{leftbar}\ifULt@final\else\internallinenumbers\fi%
	}
	\theorempostwork{\end{leftbar}}
\fi
\newaliascnt{definition}{theorem}
\newtheorem{definition}[definition]{Definition}
\aliascntresetthe{definition}

\newaliascnt{conjecture}{theorem}
\newtheorem{conjecture}[conjecture]{Conjecture}
\aliascntresetthe{conjecture}

\ifthenelse{\equal{\val@fontloader}{unicode-math}}{%
	% workaround for unicode-math defining \question
	\AtBeginDocument{%
		\let\question=\undefined%
		\theoremstyle{doug}%
		\theoremsymbol{}%
		\newaliascnt{question}{theorem}
		\newtheorem{question}[question]{Question}
		\aliascntresetthe{question}
	}%
}{%
	\newaliascnt{question}{theorem}
	\newtheorem{question}[question]{Question}
	\aliascntresetthe{question}
}

\newaliascnt{example}{theorem}
\newtheorem{example}[example]{Example}
\aliascntresetthe{example}

\newtheoremstyle{pf}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\ ##2\theorem@separator]}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\ ##2\ (##3)\theorem@separator]}
\newtheoremstyle{nonumberpf}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\theorem@separator]}%
	{\item[\hskip\labelsep \theorem@headerfont ##3\theorem@separator]}
\theoremheaderfont{\normalfont\itshape}
\theorembodyfont{\normalfont}
\theoremseparator{.}
\ifULt@fancyproof
	\theoremsymbol{
		\begin{tikzpicture}[baseline=(bl)]
			\path[use as bounding box] (-\@memptsize pt,-0.45*\@memptsize pt) rectangle (\@memptsize pt,0.45*\@memptsize pt);
			\foreach \v in {0,...,5}\node[vertex,inner sep=1.1pt] (ULtv\v) at (60*\v:0.75*\@memptsize pt){};
			\foreach \u in {0,...,4}{
				\pgfmathtruncatemacro{\upl}{\u+1}
				\foreach \v in {\upl,...,5} \draw (ULtv\u) -- (ULtv\v);
			}
			\coordinate (bl) at (0,{-0.25*sqrt(3)*\@memptsize pt});
		\end{tikzpicture}
	}
\else \theoremsymbol{\ensuremath{\Box}} \fi

\theoremstyle{pf}
\newtheorem*{proof}{Proof}

\ifULt@fancyproof
	\theoremsymbol{%
		\begin{tikzpicture}[baseline=(bl)]
			\path[use as bounding box] (-\@memptsize pt,-0.45*\@memptsize pt) rectangle (\@memptsize pt,0.45*\@memptsize pt);
			\node[vertex,inner sep=1.1pt] (ULtv1) at (0.75*\@memptsize pt,0){};
			\node[vertex,inner sep=1.1pt] (ULtv2) at (-0.75*\@memptsize pt,0){};
			\draw (ULtv1) -- (ULtv2);
			\coordinate (bl) at (0,{-0.25*sqrt(3)*\@memptsize pt});
		\end{tikzpicture}
	}
\else \theoremsymbol{} \fi
\theoremseparator{:}
\theoremheaderfont{\normalfont\scshape}
\newtheorem*{claim}{Claim}

\newtheoremstyle{case}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\ ##2\theorem@separator]}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\ ##2\ (##3)\theorem@separator]}
\newtheoremstyle{nonumbercase}%
	{\item[\hskip\labelsep \theorem@headerfont ##1\theorem@separator]}%
	{\item[\hskip\labelsep \theorem@headerfont ##3\theorem@separator]}
\theoremheaderfont{\normalfont\bfseries}
\theorembodyfont{\normalfont}
\theoremseparator{.}
\ifULt@fancyproof
	\theoremsymbol{%
		\begin{tikzpicture}[baseline=(bl)]
			\path[use as bounding box] (-\@memptsize pt,-0.45*\@memptsize pt) rectangle (\@memptsize pt,0.45*\@memptsize pt);
			\foreach \v in {0,...,3}\node[vertex,inner sep=1.1pt] (ULtv\v) at (90*\v:0.75*\@memptsize pt){};
			\foreach \u in {0,...,2}{
				\pgfmathtruncatemacro{\upl}{\u+1}
				\foreach \v in {\upl,...,3} \draw (ULtv\u) -- (ULtv\v);
			}
			\coordinate (bl) at (0,{-0.25*sqrt(3)*\@memptsize pt});
		\end{tikzpicture}
	}
\else \theoremsymbol{} \fi

\theoremstyle{case}
\newtheorem{case}{Case}

\ifULt@fancyproof
	\theoremsymbol{%
		\begin{tikzpicture}[baseline=(bl)]
			\path[use as bounding box] (-\@memptsize pt,-0.45*\@memptsize pt) rectangle (\@memptsize pt,0.45*\@memptsize pt);
			\foreach \v in {0,...,2}\node[vertex,inner sep=1.1pt] (ULtv\v) at (90+120*\v:0.5*\@memptsize pt){};
			\draw (ULtv0) -- (ULtv1) -- (ULtv2) -- (ULtv0);
			\coordinate (bl) at (0,0);
		\end{tikzpicture}
	}
\else \theoremsymbol{} \fi
\newtheorem{subcase}{Case}[case]


% fields that user can set (in addition to title, author, etc)
	\newcommand{\degrees}[1]{\def\ULt@degrees{#1}}
	\newcommand*{\graduationdate}[1]{\def\ULt@gdate{#1}}
	\newcommand*{\defensedate}[1]{\def\ULt@ddate{#1}}
	\newcommand*{\email}[1]{\def\ULt@email{#1}}
	\newcommand*{\phone}[1]{\def\ULt@phone{#1}}
	\newcommand{\address}[2]{\def\ULt@addressa{#1} \def\ULt@addressb{#2}}
	\degrees{Diploma, Elementary School, 2022}
	\graduationdate{July 2040}
	\defensedate{22 June 2040}
	\email{email@address.com}
	\phone{555-555-5555}
	\address{12309 Cantara St.}{Los Angeles, CA 91605}

% title
\renewcommand{\maketitle}{%
	\bgroup\ULt@singlespacing%
	\thispagestyle{empty}\ULt@topspace{1in}%
	\begin{center}%
		\MakeUppercase{\@title}%
		\vfill%
		By\\[\baselineskip]
		\@author\\
		\ULt@degrees
		\vfill%
		A Dissertation\\
		Submitted to the Faculty of the\\
		College of Arts and Sciences of the University of Louisville\\
		in Partial Fulfillment of the Requirements\\
		for the Degree of
		\vfill
		Doctor of Philosophy
		\vfill
		Department of Mathematics\\
		University of Louisville\\
		Louisville, Kentucky
		\vfill
		\ULt@gdate
		\vfill
	\end{center}
	\egroup\clearpage%
}

% copyright
\newenvironment{copyrightinfo}{%
	\ULt@doublespacing\thispagestyle{empty}\ULt@topspace{2in}%
	\begin{center}%
}{%
	\end{center}%
	\clearpage\thispagestyle{empty}\null\clearpage%
}

% signature page
% created with newcommand.py
% Prototype: MACRO signaturepage OPT[#1={5}] OPT[#2={}, #3={}, #4={}, #5={}, #6={}, #7={}, #8={}, #9={}]
\newcommand{\signaturepage}[1][5]{%
  \@ifnextchar[{\signaturepage@i[{#1}]}{\signaturepage@i[{#1}][{}]}%
}

\def\signaturepage@i[#1][#2]{%
  \@ifnextchar[{\signaturepage@ii[{#1}][{#2}]}{\signaturepage@ii[{#1}][{#2}][{}]}%
}

\def\signaturepage@ii[#1][#2][#3]{%
  \@ifnextchar[{\signaturepage@iii[{#1}][{#2}][{#3}]}{\signaturepage@iii[{#1}][{#2}][{#3}][{}]}%
}

\def\signaturepage@iii[#1][#2][#3][#4]{%
  \@ifnextchar[{\signaturepage@iv[{#1}][{#2}][{#3}][{#4}]}{\signaturepage@iv[{#1}][{#2}][{#3}][{#4}][{}]}%
}

\def\signaturepage@iv[#1][#2][#3][#4][#5]{%
  \@ifnextchar[{\signaturepage@v[{#1}][{#2}][{#3}][{#4}][{#5}]}{\signaturepage@v[{#1}][{#2}][{#3}][{#4}][{#5}][{}]}%
}

\def\signaturepage@v[#1][#2][#3][#4][#5][#6]{%
  \@ifnextchar[{\signaturepage@vi[{#1}][{#2}][{#3}][{#4}][{#5}][{#6}]}{\signaturepage@vi[{#1}][{#2}][{#3}][{#4}][{#5}][{#6}][{}]}%
}

\def\signaturepage@vi[#1][#2][#3][#4][#5][#6][#7]{%
  \@ifnextchar[{\signaturepage@vii[{#1}][{#2}][{#3}][{#4}][{#5}][{#6}][{#7}]}{\signaturepage@vii[{#1}][{#2}][{#3}][{#4}][{#5}][{#6}][{#7}][{}]}%
}

\def\signaturepage@vii[#1][#2][#3][#4][#5][#6][#7][#8]{%
  \@ifnextchar[{\signaturepage@viii[{#1}][{#2}][{#3}][{#4}][{#5}][{#6}][{#7}][{#8}]}{\signaturepage@viii[{#1}][{#2}][{#3}][{#4}][{#5}][{#6}][{#7}][{#8}][{}]}%
}

\def\signaturepage@viii[#1][#2][#3][#4][#5][#6][#7][#8][#9]{%
	\bgroup\ULt@singlespacing\ULt@topspace{1in}%
	\setcounter{page}{2}\def\ULt@ddname{#2}%
	\begin{center}
		\MakeUppercase{\@title}\\[\baselineskip]
		By\\[\baselineskip]
		\@author\\
		\ULt@degrees\\[\baselineskip]
		A Dissertation Approved on
		\vfill
		\ULt@ddate
		\vfill
		by the following Dissertation Committee:
		\vfill
		\ifthenelse{#1 > 0}{%
			\underline{\hspace{3in}}\\
			\ifx\ULt@ddname\empty
				Dissertation Director%
			\else
				#2, Dissertation Director%
			\fi
			\vfill
		}{}
		\ifthenelse{#1 > 1}{%
			\underline{\hspace{3in}}\\
			#3
			\vfill
		}{}
		\ifthenelse{#1 > 2}{%
			\underline{\hspace{3in}}\\
			#4
			\vfill
		}{}
		\ifthenelse{#1 > 3}{%
			\underline{\hspace{3in}}\\
			#5
			\vfill
		}{}
		\ifthenelse{#1 > 4}{%
			\underline{\hspace{3in}}\\
			#6
			\vfill
		}{}
		\ifthenelse{#1 > 5}{%
			\underline{\hspace{3in}}\\
			#7
			\vfill
		}{}
		\ifthenelse{#1 > 6}{%
			\underline{\hspace{3in}}\\
			#8
			\vfill
		}{}
		\ifthenelse{#1 > 7}{%
			\underline{\hspace{3in}}\\
			#9
			\vfill
		}{}
	\end{center}
	\egroup\clearpage%
}

% dedication
\newenvironment{dedication}{%
	\ULt@doublespacing%\thispagestyle{empty}
	\ULt@topspace{1in}%
	\begin{center}%
}{%
	\end{center}\clearpage%
}

% acknowledgements
\newenvironment{acknowledgements}{%
	\chapter{ACKNOWLEDGEMENTS}%
}{%
}

% abstract
\renewenvironment{abstract}{%
	\chapter{ABSTRACT}%
	{\centering\@title\par
	\@author\par
	\ULt@ddate\par}
}{%
}

% CV
\newenvironment{vita}{%
	\chapter{CURRICULUM VIT\AE}%
	\begin{center}%
		\@author
	\end{center}%
	\ULt@singlespacing
}{

}

% revision of structural commands
\let\ULt@tableofcontents\tableofcontents
\renewcommand{\tableofcontents}{\clearpage\ULt@tableofcontents}

\let\ULt@listoftables\listoftables
\renewcommand{\listoftables}{\clearpage\ULt@listoftables}

\let\ULt@listoffigures\listoffigures
\renewcommand{\listoffigures}{\clearpage\ULt@listoffigures}

\let\ULt@frontmatter\frontmatter
\renewcommand{\frontmatter}{%
	\addtocontents{toc}{\protect\begin{SingleSpace}}%
	\ULt@frontmatter%
}

\let\ULt@mainmatter\mainmatter
\renewcommand{\mainmatter}{
	\addtocontents{toc}{\protect\end{SingleSpace}}%
	\ULt@mainmatter\ULt@doublespacing%
}

\let\ULt@memappendix\appendix
\renewcommand{\appendix}{\ULt@memappendix\setsecnumdepth{chapter}}

% appearance tweaks
\pagestyle{chapter}
\setlength{\delimitershortfall}{-1pt}
\AtBeginDocument{\ULt@doublespacing}
\frenchspacing

\RequirePackage{enumitem}
\setenumerate{nolistsep,leftmargin=2\parindent}
\setenumerate[1]{label=(\roman*), ref=(\roman*)}
\setenumerate[2]{label=(\alph*),ref=(\roman{enumi}.\alph*)}
\setitemize{nolistsep}

\setlength{\topsep}{0pt}
\setlength{\partopsep}{0pt}
\setlength{\parsep}{0pt}

\newlength{\ULt@topspacelen}
\newcommand*{\ULt@topspace}[1]{%
	\setlength{\ULt@topspacelen}{#1-\baselineskip}%
	\vspace*{\ULt@topspacelen}%
}

\let\ULt@memDoubleSpacing\DoubleSpacing
\renewcommand{\DoubleSpacing}{%
	\ULt@memDoubleSpacing%
	\setlength{\abovedisplayshortskip}{0.5\baselineskip plus 0.25\baselineskip minus 0.5\baselineskip}%{0pt plus 6pt minus 6pt}%
	\setlength{\belowdisplayshortskip}{0.5\baselineskip plus 0.25\baselineskip minus 0.5\baselineskip}%{0pt plus 6pt minus 6pt}%
	\setlength{\abovedisplayskip}{0.5\baselineskip plus 0.25\baselineskip minus 0.5\baselineskip}%{12pt plus 9pt minus 12pt}%
	\setlength{\belowdisplayskip}{0.5\baselineskip plus 0.25\baselineskip minus 0.5\baselineskip}%{12pt plus 9pt minus 12pt}%
}

%\newcommand{\ULt@doublespacing}{\relax}
\newcommand{\ULt@doublespacing}{\DoubleSpacing}
%\newcommand{\ULt@doublespacing}{\linespread{2}\selectfont}

\newcommand{\ULt@singlespacing}{\SingleSpacing}

\AtEndOfClass{\typeout{}\typeout{}}

\makechapterstyle{louisville}{
	\renewcommand*{\chapnumfont}{\normalfont\bfseries}
	\renewcommand*{\chapnamefont}{\normalfont\bfseries}
	\renewcommand*{\chaptitlefont}{\normalfont\bfseries}
	\renewcommand*{\printchaptername}{\centering\chapnamefont\MakeUppercase{\@chapapp}}
	\renewcommand*{\chapternamenum}{\space}
	\renewcommand*{\printchapternum}{\chapnumfont \thechapter}
	%\renewcommand*{\printchapternonum}{\vspace{\baselineskip}}
	\renewcommand{\printchaptertitle}[1]{\centering\chaptitlefont ##1}
	\renewcommand*{\chapterheadstart}{\ULt@topspace{\beforechapskip}}
	\setlength{\beforechapskip}{1in}
	\setlength{\midchapskip}{0pt}
	\setlength{\afterchapskip}{0pt}
}
\chapterstyle{louisville}

\newcommand*{\forcepar}[1]{#1\par}

\setsecheadstyle{\bfseries\centering\forcepar}
\setsecnumformat{\csname the#1\endcsname\ --\ }
%\setbeforesecskip{0pt}
\setaftersecskip{0pt}

\setsubsecheadstyle{\bfseries\centering\forcepar}
\setbeforesubsecskip{0pt}
\setaftersubsecskip{0pt}


\setlength{\cftparskip}{0pt}
\setlength{\cftbeforechapterskip}{0pt}
\renewcommand{\cftchapterleader}{\cftdotfill{\cftchapterdotsep}}
\renewcommand{\cftchapterdotsep}{\cftdotsep}
\renewcommand{\cftchapterfont}{}
\renewcommand{\cftchapterpagefont}{}
\indentafterchapter
\renewcommand{\contentsname}{TABLE OF CONTENTS}
\renewcommand{\insertchapterspace}{} % p. 82


% Creative Commons license icons
\input{ul-thesis.ccicons.def}
\endinput