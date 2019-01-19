{-
******************************************************************************
*                                  H M T C                                   *
*                                                                            *
*       Module:         Token                                                *
*       Purpose:        Representation of tokens (lexical symbols)           *
*       Authors:        Henrik Nilsson                                       *
*                                                                            *
*                 Copyright (c) Henrik Nilsson, 2006 - 2012                  *
*                                                                            *
******************************************************************************
-}

-- | Representation of tokens (lexical symbols).

module Token where

-- HMTC module imports
import Name


-- | Token type.

data Token
    -- Graphical tokens
    = LPar      -- ^ \"(\"
    | RPar      -- ^ \")\"
    | Comma     -- ^ \",\"
    | Semicol   -- ^ \";\"
    | Colon     -- ^ \":\"
    | ColEq     -- ^ \":=\"
    | Equals    -- ^ \"=\"
    | Cond      -- ^ \"?\"          TASK I.2

    -- Keywords
    | Begin     -- ^ \"begin\"
    | Const     -- ^ \"const\"
    | Do        -- ^ \"do\"
    | Else      -- ^ \"else\"
    | End       -- ^ \"end\"
    | If        -- ^ \"if\"
    | In        -- ^ \"in\"
    | Let       -- ^ \"let\"
    | Then      -- ^ \"then\"
    | Var       -- ^ \"var\"
    | While     -- ^ \"while\"
    | Repeat    -- ^ \"repeat\"     TASK I.1
    | Until     -- ^ \"until\"      TASK I.1
    | Elsif     -- ^ \"elsif\"      TASK I.3

    -- Tokens with variable spellings
    | LitInt {liVal :: Integer}         -- ^ Integer literals
    | LitChar {lcVal :: Char}
    | Id     {idName :: Name}           -- ^ Identifiers
    | Op     {opName :: Name}           -- ^ Operators

    -- End Of File marker
    | EOF                               -- ^ End of file (input) marker.
    deriving (Eq, Show)
