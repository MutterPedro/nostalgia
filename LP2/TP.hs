import System.Random 
import System.IO.Unsafe

menorValorLista (a:x) = menor a x
menor valor [] = valor
menor valor (a:x) | valor > a = menor a x
				  | otherwise = menor valor x



corteAleatorio:: Int->[Int]->[Int]
corteAleatorio t (cab:corpo) | t > menorValorLista (cab:corpo) = heuristicaAleatoria t (cab:corpo) []
							 | otherwise = [t]

pegarAleatorio lista = lista !! unsafePerformIO(randomRIO(0,((length lista) - 1)))

heuristicaAleatoria t lista cortes | t < menorValorLista lista = (t:cortes)
								   | c <- pegarAleatorio lista, t >= c = heuristicaAleatoria (t-c) lista (c:cortes)
								   | otherwise = heuristicaAleatoria t lista cortes


corteMultiplos:: Int->[Int]->[Int]
corteMultiplos t lista | t > menorValorLista lista = heuristicaMultiplos t lista []
					   | otherwise = [t]

buscarMultiplo t [] = 0
buscarMultiplo t (a:x) | (mod t a) == 0 = a
					   | otherwise = buscarMultiplo t x

buscarMultiploSoma t [] = [0]
buscarMultiploSoma t (a:[]) = [0]
buscarMultiploSoma t (a:x) | (mod t (a+head x)) == 0 = [a,head x]
						   | otherwise = buscarMultiploSoma t x

heuristicaMultiplos t lista cortes | t < menorValorLista lista = (t:cortes)
								   | c <- buscarMultiplo t lista, c > 0 = heuristicaMultiplos (t-c) lista (c:cortes)
								   | d <- buscarMultiploSoma t lista, (sum d) > 0 = heuristicaMultiplos (t - sum d) lista (head d:(d !! 1):cortes)
								   | e <- pegarAleatorio lista, t >= e = heuristicaMultiplos (t-e) lista (e:cortes)
								   | otherwise = heuristicaMultiplos t lista cortes
